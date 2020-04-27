SELECT t1.title
FROM (SELECT title
  FROM movies
  WHERE id IN (SELECT movie_id
  FROM stars
  WHERE person_id IN (SELECT id
  FROM people
  WHERE name = "Johnny Depp"))) as t1, (SELECT title
  FROM movies
  WHERE id IN (SELECT movie_id
  FROM stars
  WHERE person_id IN (SELECT id
  FROM people
  WHERE name = "Helena Bonham Carter"))) as t2
WHERE t1.title = t2.title;