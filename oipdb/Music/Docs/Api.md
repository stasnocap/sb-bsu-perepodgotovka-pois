# Music Api

- [Music API](#music-api)
  - [Auth](#auth) 
    - [Register](#register)
      - [Register Request](#register-request) 
      - [Register Response](#register-response)
    - [Login](#login)
      - [Login Request](#login-request)
      - [Login Response](#login-response)

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