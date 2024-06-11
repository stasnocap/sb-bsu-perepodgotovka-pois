using ErrorOr;
using MediatR;
using Microsoft.AspNetCore.Identity;
using Music.Application.Authentication.Common;
using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.User;
using Music.Domain.User.Errors;
using Music.Domain.User.ValueObjects;

namespace Music.Application.Authentication.Commands.Register;

public class RegisterCommandHandler(
    IUserRepository _userRepository,
    IJwtTokenGenerator _jwtTokenGenerator,
    IPasswordHasher<User> _passwordHasher)
    : IRequestHandler<RegisterCommand, ErrorOr<AuthenticationResult>>
{
    public async Task<ErrorOr<AuthenticationResult>> Handle(RegisterCommand request,
        CancellationToken cancellationToken)
    {
        if (await _userRepository.SingleOrDefaultAsync(request.Email, cancellationToken) is not null)
        {
            return Errors.User.DuplicateEmail;
        }

        var errors = new List<Error>();

        var errorOrFirstName = FirstName.Create(request.FirstName);
        errors.AddRange(errorOrFirstName.ErrorsOrEmptyList);
        var errorOrLastName = LastName.Create(request.LastName);
        errors.AddRange(errorOrLastName.ErrorsOrEmptyList);
        var errorOrEmail = Email.Create(request.Email);
        errors.AddRange(errorOrEmail.ErrorsOrEmptyList);
        var errorOrPassword = Password.Create(request.Password);
        errors.AddRange(errorOrPassword.ErrorsOrEmptyList);

        if (errors.Any())
        {
            return errors;
        }

        var firstName = errorOrFirstName.Value;
        var lastName = errorOrLastName.Value;
        var email = errorOrEmail.Value;
        var password = errorOrPassword.Value;

        var user = User.Create(firstName, lastName, email);

        var errorOrPasswordHash = PasswordHash.Create(_passwordHasher.HashPassword(user, password.Value));
        errors.AddRange(errorOrPassword.ErrorsOrEmptyList);

        if (errors.Any())
        {
            return errors;
        }

        user.PasswordHash = errorOrPasswordHash.Value;

        await _userRepository.AddAsync(user, cancellationToken);

        var token = _jwtTokenGenerator.GenerateToken(user);

        return new AuthenticationResult(user, request.Email, token);
    }
}