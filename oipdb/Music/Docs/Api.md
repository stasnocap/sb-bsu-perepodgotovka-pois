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
New Name
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