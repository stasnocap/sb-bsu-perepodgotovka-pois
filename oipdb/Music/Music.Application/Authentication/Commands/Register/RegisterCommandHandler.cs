using ErrorOr;
using MediatR;
using Music.Application.Authentication.Common;
using Music.Application.Common.Interfaces.Authentication;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.User;
using Music.Domain.User.Errors;

namespace Music.Application.Authentication.Commands.Register;

public class RegisterCommandHandler(IUserRepository userRepository, IJwtTokenGenerator jwtTokenGenerator)
    : IRequestHandler<RegisterCommand, ErrorOr<AuthenticationResult>>
{
    public async Task<ErrorOr<AuthenticationResult>> Handle(RegisterCommand request,
        CancellationToken cancellationToken)
    {
        if (await userRepository.GetUserByEmailAsync(request.Email, cancellationToken) is not null)
        {
            return Errors.User.DuplicateEmail;
        }

        var user = User.Create(request.FirstName, request.LastName, request.Email, request.Password);

        await userRepository.AddAsync(user, cancellationToken);

        var token = jwtTokenGenerator.GenerateToken(user);

        return new AuthenticationResult(user, request.Email, token);
    }
}