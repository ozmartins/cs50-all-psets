select name
from movies
join stars on (stars.movie_id = movies.id)
join people on (people.id = stars.person_id)
where title like 'Toy Story';