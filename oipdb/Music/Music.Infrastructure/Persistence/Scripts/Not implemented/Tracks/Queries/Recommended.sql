
-- получить жанры которые лайкает пользователь
with genres as (select "GenreId"
from "LikedTracks"
join public."Tracks" T on T."Id" = "LikedTracks"."TrackId"
join public."Genres" G on G."Id" = T."GenreId"
where "UserId" = '00176d52-0601-4843-9ac3-ecc931f8585c')

-- рекомендованные популярные треки по жанрам
select A."Name" as "Artist", "Tracks"."Name" as "Track"
from "Tracks"
join public."Genres" G on G."Id" = "Tracks"."GenreId"
join public."LikedTracks" LT on "Tracks"."Id" = LT."TrackId"
join public."Artists" A on "Tracks"."ArtistId" = A."Id"
where "GenreId" in (select "GenreId" from genres) and LT."UserId" <> '00176d52-0601-4843-9ac3-ecc931f8585c'
limit 10;


select * from "LikedTracks";
select * from "Genres";