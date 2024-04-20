with Artist as (
    insert into "Artists" ("Name")
        values ('Yeat')
        returning "Artists"."Id"),
     Album as (insert into "Albums" ("ArtistId", "Name")
         select Artist."Id",
                ('Up 2 me')
         from Artist
         returning "Albums"."Id", "ArtistId")
insert into "Tracks" ("ArtistId", "AlbumId", "Name")
select "ArtistId", Album."Id", 'Cmon'
from Album;