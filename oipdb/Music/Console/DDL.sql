create table "Artists"
(
    "Id"   integer generated always as identity
        primary key,
    "Name" varchar(255) not null
);

create table "Albums"
(
    "Id"   integer generated always as identity
            primary key,
    "Name" varchar(255) not null
);

create table "Tracks"
(
    "Id"       integer generated always as identity
        primary key,
    "ArtistId" bigint
        constraint fk_artist
            references "Artists"
            on delete cascade,
    "AlbumId"  bigint
        constraint fk_album
            references "Albums"
            on delete cascade,
    "Name"     varchar(255) not null
);

create table "Users"
(
    "Id"   integer generated always as identity
        primary key,
    "Name" varchar(255) not null
);

create table "LikedTracks"
(
    "Id"      integer generated always as identity
        primary key,
    "TrackId" bigint
        constraint fk_track
            references "Tracks"
            on delete cascade,
    "UserId"  bigint
        constraint fk_user
            references "Users"
            on delete cascade
);

create table "Followers"
(
    "Id"       integer generated always as identity
        primary key,
    "ArtistId" bigint
        constraint fk_artist
            references "Artists"
            on delete cascade,
    "UserId"   bigint
        constraint fk_user
            references "Users"
            on delete cascade
);

