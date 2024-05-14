using MediatR;
using Music.Application.Services;

namespace Music.Application.Authentication.Queries.Login;

public record LoginQuery(string Email, string Password) : IRequest<ErrorOr.ErrorOr<AuthenticationResult>>;