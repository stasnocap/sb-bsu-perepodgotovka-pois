using ErrorOr;
using MediatR;
using Music.Application.Authentication.Common;
using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.User;
using Music.Domain.User.Errors;

namespace Music.Application.Authentication.Queries.Login;

public class LoginQueryHandler(IUserRepository userRepository, IJwtTokenGenerator jwtTokenGenerator)
    : IRequestHandler<LoginQuery, ErrorOr<AuthenticationResult>>
{
    public async Task<ErrorOr<AuthenticationResult>> Handle(LoginQuery request, CancellationToken cancellationToken)
    {
        await Task.CompletedTask;
        
        if (await userRepository.GetUserByEmailAsync(request.Email, cancellationToken) is not { } user)
        {
            return Errors.User.DuplicateEmail;
        }

        if (user.Password != request.Password)
        {
            return Errors.Authentication.InvalidCredentials;
        }

        var token = jwtTokenGenerator.GenerateToken(user);

        return new AuthenticationResult(user, request.Email, token);
    }
}