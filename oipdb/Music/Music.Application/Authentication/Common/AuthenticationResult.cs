using Music.Domain.User;

namespace Music.Application.Authentication.Common;

public record AuthenticationResult(
    User User,
    string Email,
    string Token);