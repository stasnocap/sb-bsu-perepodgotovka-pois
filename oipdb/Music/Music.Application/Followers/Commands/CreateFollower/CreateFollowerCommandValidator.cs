using FluentValidation;

namespace Music.Application.Followers.Commands.CreateFollower;

public class CreateFollowerCommandValidator : AbstractValidator<CreateFollowerCommand>
{
    public CreateFollowerCommandValidator()
    {
        RuleFor(c => c.ArtistId).NotEmpty();
    }
}