using ErrorOr;
using MediatR;
using Music.Application.Authentication.Common;
using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.User;
using Music.Domain.User.Errors;
using Music.Domain.User.ValueObjects;

namespace Music.Application.Authentication.Commands.Register;

public class RegisterCommandHandler(IUserRepository userRepository, IJwtTokenGenerator jwtTokenGenerator)
    : IRequestHandler<RegisterCommand, ErrorOr<AuthenticationResult>>
{
    public async Task<ErrorOr<AuthenticationResult>> Handle(RegisterCommand request,
        CancellationToken cancellationToken)
    {
        if (await userRepository.SingleOrDefaultAsync(request.Email, cancellationToken) is not null)
        {
            return Errors.User.DuplicateEmail;
        }

        var errors = new List<Error>();

        var firstName = FirstName.Create(request.FirstName);
        errors.AddRange(firstName.ErrorsOrEmptyList);
        var lastName = LastName.Create(request.LastName);
        errors.AddRange(lastName.ErrorsOrEmptyList);
        var email = Email.Create(request.LastName);
        errors.AddRange(email.ErrorsOrEmptyList);
        var password = Password.Create(request.LastName);
        errors.AddRange(email.ErrorsOrEmptyList);

        if (errors.Any())
        {
            return errors;
        }

        var user = User.Create(firstName.Value, lastName.Value, email.Value, password.Value);

        await userRepository.AddAsync(user, cancellationToken);

        var token = jwtTokenGenerator.GenerateToken(user);

        return new AuthenticationResult(user, request.Email, token);
    }
}