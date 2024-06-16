using FluentValidation;

namespace Music.Application.Artists.Commands.ChangeArtistName;

public class ChangeArtistNameCommandValidator : AbstractValidator<ChangeArtistNameCommand>
{
    public ChangeArtistNameCommandValidator()
    {
        RuleFor(c => c.Name).NotEmpty();
    }
}