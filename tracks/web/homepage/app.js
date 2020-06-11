const data = {
  years: null,
  months: null,
  weeks: null,
  days: null,
  hours: null,
  minutes: null,
  seconds: null,
  time: 1586092440000 // Epoch timestamp, since April 5, 2020 8:14 PM WIB
};

const progresses = document.querySelectorAll(".progres[fraction]");

update();

function update() {
  const now = new Date().getTime();
  const seconds = (now - data.time) / 1000;
  data.years = seconds / 31556952;
  data.months = seconds / 2592000;
  data.weeks = seconds / 604800;
  data.days = seconds / 86400;
  data.hours = seconds / 3600;
  data.minutes = seconds / 60;
  data.seconds = seconds;
  updatePies();
  requestAnimationFrame(update);
}

function updatePies() {
  const radius = 25;
  const circumference = radius * 2 * Math.PI;
  progresses.forEach(progres => {
    const value = data[progres.getAttribute("fraction")];
    const complete = Math.floor(value);
    let v = complete.toString().replace(/\B(?=(\d{3})+(?!\d))/g, ".");
    if (complete < 10) v = value.toFixed(2).replace(".", ",");
    if (complete < 1) v = value.toFixed(3).replace(".", ",");
    progres.querySelector("h2").innerText = v;
    const percent = Math.round((value - complete) * 100 * 10) / 10;
    const offset = circumference - (percent / 100) * circumference;
    progres.querySelector(
      ".left"
    ).innerHTML = `<svg xmlns="http://www.w3.org/2000/svg" height="100" width="100" viewBox="0 0 100 100">
    <circle class="bg" r="${radius}" cx="50" cy="50" />
    <circle
      class="prog"
      r="${radius}"
      cx="50"
      cy="50"
      stroke-dasharray="${circumference} ${circumference}"
      stroke-dashoffset="${offset}"
    />
  </svg>`;
  });
}
