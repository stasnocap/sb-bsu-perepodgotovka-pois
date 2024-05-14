using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.Common.Errors;
using Music.Domain.Entities;

namespace Music.Application.Services;

public class AuthenticationService(IJwtTokenGenerator jwtTokenGenerator, IUserRepository userRepository)
    : IAuthenticationService
{
    public ErrorOr.ErrorOr<AuthenticationResult> Register(string firstName, string lastName, string email, string password)
    {
        if (userRepository.GetUserByEmail(email) is not null)
        {
            return Errors.User.DuplicateEmail;
        }

        var user = new User
        {
            FirstName = firstName,
            LastName = lastName,
            Email = email,
            Password = password
        };

        userRepository.Add(user);

        var token = jwtTokenGenerator.GenerateToken(user);

        return new AuthenticationResult(user, email, token);
    }

    public ErrorOr.ErrorOr<AuthenticationResult> Login(string email, string password)
    {
        if (userRepository.GetUserByEmail(email) is not User user)
        {
            return Errors.User.DuplicateEmail;
        }

        if (user.Password != password)
        {            
            return Errors.Authentication.InvalidCredentials;
        }

        var token = jwtTokenGenerator.GenerateToken(user);

        return new AuthenticationResult(user, email, token);
    }
}