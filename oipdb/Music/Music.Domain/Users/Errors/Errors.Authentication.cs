﻿using ErrorOr;

namespace Music.Domain.Users.Errors;

public static partial class Errors
{
    public static class Authentication
    {
        public static Error InvalidCredentials =>
            Error.Unauthorized(code: "User.InvalidCredentials", description: "Invalid credentials.");
    }
}