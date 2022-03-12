select distinct people.name
from movies
join stars on (stars.movie_id = movies.id)
join people on (people.id = stars.person_id)
where people.name not like 'Kevin Bacon'
and movies.id in (select s.movie_id
                  from stars s
                  join people p on (p.id = s.person_id)
                  where p.name like 'Kevin Bacon');