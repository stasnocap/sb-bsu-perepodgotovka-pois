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
    "Id"   uuid default gen_random_uuid() not null
        primary key,
    "Name" varchar(255)                   not null
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