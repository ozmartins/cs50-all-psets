select distinct people.name
from directors
join people on (people.id = directors.person_id)
join movies on (movies.id = directors.movie_id)
join ratings on (ratings.movie_id = movies.id)
where rating >= 9;