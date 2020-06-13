import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get current session user id
    user_id = session["user_id"]
    
    # Get list of stock
    stock_list = db.execute("SELECT symbol, owned_shares \
                            FROM(SELECT symbol, SUM(shares) as owned_shares \
                                FROM transactions \
                                WHERE user_id=:user_id \
                                GROUP BY symbol) \
                            WHERE owned_shares > 0", user_id=user_id)
    rows = len(stock_list)
    wealth = 0

    # Update list from api
    for i in range(rows):

        # Fetch api
        quoted = lookup(stock_list[i]["symbol"])
        
        # Merge fetched api with db
        stock_list[i].update(quoted)

        # Calculate total
        total = stock_list[i]["price"] * stock_list[i]["owned_shares"]

        # Format with $ usd
        stock_list[i]["price"] = usd(stock_list[i]["price"])
        stock_list[i]["total"] = usd(total)

        # Calculate total wealth
        wealth += total
    
    # Get total cash from db
    fetch_cash = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=user_id)
    cash = usd(fetch_cash[0]["cash"])
    wealth = usd(wealth + fetch_cash[0]["cash"])

    # Render main page
    return render_template("index.html", stock_list=stock_list, cash=cash, wealth=wealth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User submit buy
    if request.method == "POST":
        
        # Get submitted data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was not blank
        if not symbol:
            return apology("missing symbol", 400)

        # Ensure shares was not blank
        if not shares:
            return apology("missing shares", 400)
        
        # Ensure symbol was correct
        fetch = lookup(symbol)
        if fetch == None:
            return apology("invalid symbol", 400)
        
        # Cast value
        shares = int(shares)
        price = fetch["price"]

        # Get current session user
        user_id = session["user_id"]

        # Get current available cash
        cash = db.execute(
            "SELECT cash FROM users WHERE id = :id", id=user_id)[0]["cash"]
        
        # Calculate cashflow
        bought = price * shares
        cash -= bought
        
        # Ensure cash has to be positive
        if cash < 0:
            return apology("can't afford", 400)
        
        # Process buy
        # Store information into transactions table
        db.execute(
            "INSERT INTO transactions(user_id, symbol, shares, price, date) \
            VALUES(:user_id, :symbol, :shares, :price, DATETIME('now'))",
            user_id=user_id,
            symbol=symbol.upper(),
            shares=shares,
            price=price
        )

        # update users table
        db.execute(
            "UPDATE users SET cash = :cash WHERE id = :id",
            id=user_id,
            cash=cash
        )

        # Redirect to index
        flash("Bought!")
        return redirect("/")
            
    
    # User request GET buy
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Get current session user id
    user_id = session["user_id"]

    # Get tx list from database
    tx_list = db.execute("SELECT symbol, shares, price, date FROM transactions \
                          WHERE user_id = :user_id", user_id=user_id)

    # Format price with $ usd
    for tx in tx_list:
        tx["price"] = usd(tx["price"])

    return render_template("history.html", tx_list=tx_list)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User submit quote
    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Ensure symbol was submitted
        if not symbol:
            return apology("missing symbol", 400)
        
        # Ensure valid symbol was submitted
        quoted = lookup(symbol)
        if quoted == None:
            return apology("invalid symbol", 400)

        # Render quoted page
        return render_template("quoted.html", 
                               name=quoted["name"],
                               price=usd(quoted["price"]),
                               symbol=quoted["symbol"])

    # User requested GET quote
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User submitting register form
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return redirect("/register")
        
        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure both password and confirmation was matched
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        # Query insert to database
        try:
            rows = db.execute("INSERT INTO users(username, hash) VALUES(:username, :hash)",
                         username=request.form.get("username"), 
                         hash=generate_password_hash(request.form.get("password")))
        except RuntimeError:
            flash("Username is not available")
            return redirect(url_for("register"))
        
        # # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to homepage
        flash("Registered!")
        return redirect(url_for("index"))
    
    # User requested GET method
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get current user_id
    user_id = session["user_id"]

    # User submit sell
    if request.method == "POST":

        # Get submitted data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure symbol was not blank
        if not symbol:
            return apology("missing symbol", 400)

        # Ensure shares was not blank
        if not shares:
            return apology("missing shares", 400)

        # Ensure shares was not exceeding total owned
        shares_owned = db.execute("SELECT SUM(shares) FROM transactions \
                                   WHERE user_id=:user_id AND symbol=:symbol GROUP BY symbol",
                                   user_id=user_id, symbol=symbol)[0]["SUM(shares)"]
        shares = int(shares)
        if shares > shares_owned:
            return apology("too many shares", 400)
        
        # Process sell
        price = lookup(symbol)["price"]

        # Calculate sold stock
        sold = price * shares
        
        # Get current available cash
        cash = db.execute(
            "SELECT cash FROM users WHERE id = :id", id=user_id)[0]["cash"]

        # Calculate cashflow
        cash += sold

        # Store information into transactions table
        db.execute(
            "INSERT INTO transactions(user_id, symbol, shares, price, date) \
            VALUES(:user_id, :symbol, :shares, :price, DATETIME('now'))",
            user_id=user_id,
            symbol=symbol.upper(),
            shares=-shares,
            price=price
        )

        # update users table
        db.execute(
            "UPDATE users SET cash = :cash WHERE id = :id",
            id=user_id,
            cash=cash
        )

        # Redirect to index
        flash("Sold!")
        return redirect("/")
    
    # User GET buy
    else:

        # Get list of stock
        stock_list = db.execute("SELECT symbol FROM transactions \
                                WHERE user_id=:user_id GROUP BY symbol",
                                user_id=user_id)

        # Render buy page
        return render_template("sell.html", stock_list=stock_list)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change user password"""

    # Get current session user id
    user_id = session["user_id"]

    # User submitting change password form
    if request.method == "POST":

        # Ensure old password was submitted
        if not request.form.get("old_password"):
            return redirect("/password")

        # Ensure new password was submitted
        if not request.form.get("password"):
            return apology("must provide new password", 400)

        # Ensure both new password and confirmation was matched
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("new passwords don't match", 400)

        # Query database for old password
        old_password = db.execute("SELECT hash FROM users WHERE id=:user_id",
                          user_id=user_id)[0]["hash"]
        
        # Ensure old password is correct
        if check_password_hash(old_password, request.form.get("old_password")):

            # Update the password on database
            db.execute("UPDATE users SET hash=:hash WHERE id=:user_id",
                        user_id=user_id,
                        hash=generate_password_hash(request.form.get("password")))

            # Redirect user to homepage
            flash("Password Changed!")
            return redirect(url_for("index"))
        
        flash("Old password is not correct")
        return redirect(url_for("password"))

    # User requested GET method
    else:
        return render_template("password.html")


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
