using MediatR;
using Music.Application.Authentication.Common;

namespace Music.Application.Authentication.Queries.Login;

public record LoginQuery(string Email, string Password) : IRequest<ErrorOr.ErrorOr<AuthenticationResult>>;