--write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred

SELECT t2.title
FROM (SELECT movie_id, rating
  FROM ratings
  WHERE movie_id IN (SELECT movie_id
  FROM stars
  WHERE person_id IN (SELECT id
  FROM people
  WHERE name = "Chadwick Boseman"))) as t1, (SELECT id, title
  FROM movies) as t2
WHERE t1.movie_id = t2.id
ORDER BY rating DESC
LIMIT 5;