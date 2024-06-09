create table "Artists"
(
    "Id"   uuid         not null
        primary key,
    "Name" varchar(255) not null
);

create table "Albums"
(
    "Id"   uuid         not null
        primary key,
    "Name" varchar(255) not null
);

create table "Tracks"
(
    "Id"       uuid         not null
        primary key,
    "ArtistId" uuid
        constraint fk_artist
            references "Artists"
            on delete cascade,
    "AlbumId"  uuid
        constraint fk_album
            references "Albums"
            on delete cascade,
    "Name"     varchar(255) not null
);

create table "Users"
(
    "Id"        uuid         not null
        primary key,
    "FirstName" varchar(255) not null,
    "Email"     varchar(255) not null,
    "LastName"  varchar(255) not null,
    "Password"  varchar(255) not null
);

create table "LikedTracks"
(
    "Id"      uuid not null
        primary key,
    "TrackId" uuid
        constraint fk_track
            references "Tracks"
            on delete cascade,
    "UserId"  uuid
        constraint fk_user
            references "Users"
            on delete cascade
);

create table "Followers"
(
    "Id"       uuid not null
        primary key,
    "ArtistId" uuid
        constraint fk_artist
            references "Artists"
            on delete cascade,
    "UserId"   uuid
        constraint fk_user
            references "Users"
            on delete cascade
);