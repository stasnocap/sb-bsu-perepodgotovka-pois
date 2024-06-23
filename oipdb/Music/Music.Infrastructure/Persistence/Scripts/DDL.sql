create table "Artists"
(
    "Id"   uuid default gen_random_uuid() not null
        primary key,
    "Name" varchar(255)                   not null
        unique
        constraint "Artists_Name_check"
            check (("Name")::text <> ''::text)
);

create table "Albums"
(
    "Id"        uuid                     default gen_random_uuid() not null
        primary key,
    "Name"      varchar(255)                                       not null,
    "CreatedOn" timestamp with time zone default CURRENT_TIMESTAMP
);

create table "Users"
(
    "Id"           uuid default gen_random_uuid() not null
        primary key,
    "FirstName"    varchar(255)                   not null,
    "Email"        varchar(255)                   not null,
    "LastName"     varchar(255)                   not null,
    "PasswordHash" varchar                        not null
);

create table "Followers"
(
    "Id"       uuid default gen_random_uuid() not null
        primary key,
    "ArtistId" uuid
        constraint fk_artist
            references "Artists"
            on delete cascade,
    "UserId"   uuid
        constraint fk_user
            references "Users"
            on delete cascade,
    unique ("ArtistId", "UserId")
);

create table "Genres"
(
    "Id"   uuid default gen_random_uuid() not null
        primary key,
    "Name" varchar(255)                   not null
        unique
        constraint name_not_empty
            check (("Name")::text <> ''::text)
);

create table "Tracks"
(
    "Id"       uuid default gen_random_uuid() not null
        primary key,
    "ArtistId" uuid
        constraint fk_artist
            references "Artists"
            on delete cascade,
    "AlbumId"  uuid
        constraint fk_album
            references "Albums"
            on delete cascade,
    "Name"     varchar(255)                   not null,
    "GenreId"  uuid                           not null
        constraint fk_genre
            references "Genres"
            on delete cascade
);

create table "LikedTracks"
(
    "Id"      uuid default gen_random_uuid() not null
        primary key,
    "TrackId" uuid
        constraint fk_track
            references "Tracks"
            on delete cascade,
    "UserId"  uuid
        constraint fk_user
            references "Users"
            on delete cascade,
    unique ("TrackId", "UserId")
);

create function get_tracks(search_term character varying DEFAULT NULL::character varying, page integer DEFAULT 1, page_size integer DEFAULT 10)
    returns TABLE
            (
                "Id"       uuid,
                "ArtistId" uuid,
                "AlbumId"  uuid,
                "Name"     character varying,
                "GenreId"  uuid
            )
    language plpgsql
as
$$
begin
    return query select T."Id", T."ArtistId", T."AlbumId", T."Name", T."GenreId"
                 from "Tracks" T
                          join public."Artists" Artist on Artist."Id" = T."ArtistId"
                          join public."Albums" Album on Album."Id" = T."AlbumId"
                 where search_term is null
                    or Artist."Name" ilike ('%' || search_term || '%')
                    or Album."Name" ilike ('%' || search_term || '%')
                    or T."Name" ilike ('%' || search_term || '%')
                 offset (page - 1) * page_size limit page_size;
end;
$$;

create function get_artists(search_term character varying DEFAULT NULL::character varying, page integer DEFAULT 1, page_size integer DEFAULT 10)
    returns TABLE
            (
                "Id"   uuid,
                "Name" character varying
            )
    language plpgsql
as
$$
begin
    return query select A."Id", A."Name"
                 from "Artists" A
                 where search_term is null
                    or A."Name" ilike ('%' || search_term || '%')
                 offset (page - 1) * page_size limit page_size;
end;
$$;

create function get_albums(search_term character varying DEFAULT NULL::character varying, page integer DEFAULT 1, page_size integer DEFAULT 10)
    returns TABLE
            (
                "Id"        uuid,
                "Name"      character varying,
                "CreatedOn" timestamp with time zone
            )
    language plpgsql
as
$$
begin
    return query select A."Id", A."Name"
                 from "Albums" A
                 where search_term is null
                    or A."Name" ilike ('%' || search_term || '%')
                 offset (page - 1) * page_size limit page_size;
end;
$$;

create function recommended_tracks(user_id uuid, on_date timestamp with time zone DEFAULT NULL::timestamp with time zone, count_of_first_most_liked_genres integer DEFAULT 5, search_term character varying DEFAULT NULL::character varying, page integer DEFAULT 1, page_size integer DEFAULT 10)
    returns TABLE
            (
                "TrackId"     uuid,
                "Artist Name" character varying,
                "Track Name"  character varying
            )
    language plpgsql
as
$$
declare
begin
    -- получить количество первых жанров которые пользователь лайкает больше всего
    return query with genres as (select "GenreId", count(*) as "Count Of Liked Tracks"
                                 from "LikedTracks" LT
                                          join public."Tracks" T on T."Id" = LT."TrackId"
                                          join public."Genres" G on G."Id" = T."GenreId"
                                 where "UserId" = user_id
                                 group by "GenreId"
                                 order by "Count Of Liked Tracks"
                                 limit count_of_first_most_liked_genres)

                 -- рекомендованные популярные треки по жанрам
                 select T."Id" as "TrackId", A."Name" as "Artist Name", T."Name" as "Track Name"
                 from get_tracks(search_term, page, page_size) T
                          join public."Genres" G on G."Id" = T."GenreId"
                          join public."LikedTracks" LT on T."Id" = LT."TrackId"
                          join public."Artists" A on T."ArtistId" = A."Id"
                          join public."Albums" AL on T."AlbumId" = AL."Id"
                 where "GenreId" in (select "GenreId" from genres)
                   and LT."UserId" <> user_id
                   and (case when (on_date is null) then true else "CreatedOn" > on_date end);
end;
$$;

create function fans_also_like_artists(artist_id uuid, user_id uuid, search_term character varying DEFAULT NULL::character varying, page integer DEFAULT 1, page_size integer DEFAULT 10)
    returns TABLE
            (
                "Id"   uuid,
                "Name" character varying
            )
    language plpgsql
as
$$
begin
    -- находим пользователей кто тоже подписан на нашего артиста
    return query with followers as (select F."UserId"
                                    from "Followers" F
                                    where "ArtistId" = artist_id
                                      and "UserId" <> user_id
                                    limit 5)
-- находим артистов на которые подписаны найденные пользователи
                 select F."ArtistId", A."Name" as "Artist Name"
                 from get_artists(search_term, page, page_size) A
                          join "Followers" F on f."ArtistId" = A."Id"
                 where F."UserId" in (select followers."UserId" from followers)
                   and F."ArtistId" <> artist_id
                   and F."UserId" <> user_id
                 group by F."ArtistId", A."Name"
                 order by count(*);
end;
$$;

