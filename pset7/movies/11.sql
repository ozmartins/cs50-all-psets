select distinct movies.title
from movies
join ratings on (ratings.movie_id = movies.id)
join stars on (stars.movie_id = movies.id)
join people on (people.id = stars.person_id)
where people.name like 'Chadwick Boseman'
order by ratings.rating desc
limit 5;