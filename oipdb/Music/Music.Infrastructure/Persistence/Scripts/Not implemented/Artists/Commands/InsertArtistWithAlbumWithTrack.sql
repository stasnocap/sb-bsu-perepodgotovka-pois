with Artist AS (
    insert into "Artists" ("Name")
        VALUES ('Yeat')
        returning "Artists"."Id"),
     Album AS (insert into "Albums" ("Id", "Name")
         select Artist."Id",
                ('Up 2 me')
         from Artist
         returning "Albums"."Id", "Id" AS ArtistId)
insert into "Tracks" ("ArtistId", "AlbumId", "Name")
select ArtistId, Album."Id", 'Cmon'
from Album;