# Music Api

- [Music API](#music-api)
  - [Auth](#auth) 
    - [Register](#register)
      - [Register Request](#register-request) 
      - [Register Response](#register-response)
    - [Login](#login)
      - [Login Request](#login-request)
      - [Login Response](#login-response)
  - [Artists](#artists)
    - [Create Artist](#create-artist)
      - [Create Artist Request](#create-artist-request)
      - [Create Artist Response](#create-artist-response)
    - [Change Artist Name](#change-artist-name)
      - [Change Artist Name Request](#change-artist-name-request)
      - [Change Artist Name Response](#change-artist-name-response)
    - [List Artists](#list-artists)
      - [List Artists Request](#list-artists-request)
      - [List Artists Response](#list-artists-response)
    - [List Most Popular Artists](#list-most-popular-artists)
      - [List Most Popular Artists Request](#list-most-popular-artists-request)
      - [List Most Popular Artists Response](#list-most-popular-artists-response)
    - [Fans Also Like Artists](#fans-also-like-artists)
      - [Fans Also Like Artists Request](#fans-also-like-artists-request)
      - [Fans Also Like Artists Response](#fans-also-like-artists-response)
  - [Followers](#followers)
    - [Create Follower](#create-follower)
      - [Create Follower Request](#create-follower-request)
      - [Create Follower Response](#create-follower-response)
  - [Liked Tracks](#liked-tracks)
    - [Create Liked Track](#create-liked-track)
      - [Create Liked Track Request](#create-liked-track-request)
      - [Create Liked Track Response](#create-liked-track-response)
  - [Tracks](#tracks)
    - [List Most Popular Tracks](#list-most-popular-tracks)
      - [List Most Popular Tracks Request](#list-most-popular-tracks-request)
      - [List Most Popular Tracks Response](#list-most-popular-tracks-response)
    - [List Recommended Tracks](#list-recommended-tracks)
      - [List Recommended Tracks Request](#list-recommended-tracks-request)
      - [List Recommended Tracks Response](#list-recommended-tracks-response)
    - [Discover Weekly](#discover-weekly)
      - [Discover Weekly Request](#discover-weekly-request)
      - [Discover Weekly Response](#discover-weekly-response)


## Auth

### Register

```js
POST {{host}}/auth/register
```

#### Register Request

```json
{
  "firstName": "Stas",
  "lastName": "Kapitan",
  "email": "stasnocap@gmail.com",
  "password": "Stas1232!"
}
```

### Register Response

```js
200 OK
```

```json
{
  "id": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
  "firstName": "Stas",
  "lastName": "Kapitan",
  "email": "stasnocap@gmail.com",
  "token": "token"
}
```

### Login

```js
POST {{host}}/auth/login
```

#### Login Request

```json
{
  "email": "stasnocap@gmail.com",
  "password": "Stas1232!"
}
```

### Login Response

```js
200 OK
```

```json
{
  "id": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
  "firstName": "Stas",
  "lastName": "Kapitan",
  "email": "stasnocap@gmail.com",
  "token": "token"
}
```

## Artists

### Create Artist

```js
POST {{host}}/artists
```

#### Create Artist Request

```json
{
  "name": "Ken Carson"
}
```

#### Create Artist Response

```js
201 CREATED
400 BAD REQUEST
401 UNAUTHORIZED
409 CONFLICT
```

```text
9a4b3d99-a478-41a2-aa13-019adb4e2c55
```
### Change Artist Name

```js
PUT {{host}}/artists
```

#### Change Artist Name Request

```json
{
  "id": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
  "name": "New Name"
}
```

#### Change Artist Name Response

```js
201 CREATED
400 BAD REQUEST
401 UNAUTHORIZED
404 NOT FOUND
409 CONFLICT
```

```text
9a4b3d99-a478-41a2-aa13-019adb4e2c55
```

### List Artists

```js
GET {{host}}/artists
```

#### List Artists Request

#### List Artists Response

```js
401 UNAUTHORIZED
```

```json
[
  {
    "id": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
    "name": "Ken Carson"
  },
  {
    "id": "9afbdc9e-fef6-46de-b26c-42abc9cfe040",
    "name": "Yeat"
  }
]
```

### List Most Popular Artists

```js
GET {{host}}/artists/by-popularity
```

#### List Most Popular Artists Request

#### List Most Popular Artists Response

```js
401 UNAUTHORIZED
```

```json
[
  {
    "artistId": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
    "name": "Ken Carson",
    "followers": 1
  },
  {
    "artistId": "9afbdc9e-fef6-46de-b26c-42abc9cfe040",
    "name": "Yeat",
    "followers": 10
  }
]
```

### Fans Also Like Artists

```js
GET {{host}}/artists/fans-also-like
```

#### Fans Also Like Artists Request

```json
{
  "artistid": "782bb27d-dd7a-4378-a8d4-fcbc25c04bba"
}
```

#### Fans Also Like Artists Response

```js
401 UNAUTHORIZED
```

```json
[
  {
    "artistId": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
    "artistName": "Ken Carson"
  },
  {
    "artistId": "9afbdc9e-fef6-46de-b26c-42abc9cfe040",
    "artistName": "Yeat"
  }
]
```

## Followers

### Create Follower

```js
POST {{host}}/followers
```

#### Create Follower Request

```json
{
  "artistid": "782bb27d-dd7a-4378-a8d4-fcbc25c04bba"
}
```

#### Create Follower Response

```js
401 UNAUTHORIZED
409 CONFLICT
```

```json
9a4b3d99-a478-41a2-aa13-019adb4e2c55
```

## Liked Tracks

### Like Track

```js
POST {{host}}/LikedTracks
```

#### Like Track Request

```json
{
  "trackId": "782bb27d-dd7a-4378-a8d4-fcbc25c04bba"
}
```

#### Like Track Response

```js
401 UNAUTHORIZED
409 CONFLICT
```

```json
9a4b3d99-a478-41a2-aa13-019adb4e2c55
```

## Tracks

### List Most Popular Tracks

```js
POST {{host}}/tracks/by-popularity
```

#### List Most Popular Tracks Request

#### List Most Popular Tracks Response

```js
401 UNAUTHORIZED
```

```json
[
  {
    "trackId": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
    "artistName": "Ken Carson",
    "trackName": "Private"
  },
  {
    "trackId": "9afbdc9e-fef6-46de-b26c-42abc9cfe040",
    "artistName": "Yeat",
    "trackName": "Breath"
  }
]
```

### List Recommended Tracks

```js
POST {{host}}/tracks/by-popularity
```

#### List Recommended Tracks Request

#### List Recommended Tracks Response

```js
401 UNAUTHORIZED
```

```json
[
  {
    "trackId": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
    "artistName": "Ken Carson",
    "trackName": "Private"
  },
  {
    "trackId": "9afbdc9e-fef6-46de-b26c-42abc9cfe040",
    "artistName": "Yeat",
    "trackName": "Breath"
  }
]
```

### Discover Weekly

```js
POST {{host}}/tracks/by-popularity
```

#### Discover Weekly Request

#### Discover Weekly Response

```js
401 UNAUTHORIZED
```

```json
[
  {
    "trackId": "9a4b3d99-a478-41a2-aa13-019adb4e2c55",
    "artistName": "Ken Carson",
    "trackName": "Private"
  },
  {
    "trackId": "9afbdc9e-fef6-46de-b26c-42abc9cfe040",
    "artistName": "Yeat",
    "trackName": "Breath"
  }
]
```
