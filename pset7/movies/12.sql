select title
from movies
where id in (select stars.movie_id
             from stars
             join people on (people.id = stars.person_id)
             where people.name like 'Helena Bonham Carter')
and id in (select stars.movie_id
           from stars
           join people on (people.id = stars.person_id)
           where people.name like 'Johnny Depp');