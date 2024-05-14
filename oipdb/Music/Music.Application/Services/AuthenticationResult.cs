using Music.Domain.Entities;

namespace Music.Application.Services;

public record AuthenticationResult(
    User User,
    string Email,
    string Token);