using ErrorOr;
using MediatR;
using Microsoft.AspNetCore.Identity;
using Music.Application.Authentication.Common;
using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.User;
using Music.Domain.User.Errors;

namespace Music.Application.Authentication.Queries.Login;

public class LoginQueryHandler(IUserRepository userRepository, IJwtTokenGenerator jwtTokenGenerator, IPasswordHasher<User> _passwordHasher)
    : IRequestHandler<LoginQuery, ErrorOr<AuthenticationResult>>
{
    public async Task<ErrorOr<AuthenticationResult>> Handle(LoginQuery request, CancellationToken cancellationToken)
    {
        var user = await userRepository.SingleOrDefaultAsync(request.Email, cancellationToken);
        
        if (user is null)
        {
            return Errors.User.NotFound;
        }

        var passwordVerificationResult = _passwordHasher.VerifyHashedPassword(user, user.PasswordHash.Value, request.Password);

        if (passwordVerificationResult == PasswordVerificationResult.Failed)
        {
            return Errors.Authentication.InvalidCredentials;
        }

        var token = jwtTokenGenerator.GenerateToken(user);

        return new AuthenticationResult(user, request.Email, token);
    }
}