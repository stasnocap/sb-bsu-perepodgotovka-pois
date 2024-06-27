using FluentValidation;

namespace Music.Application.LikedTracks.Commands;

public class LikeTrackCommandValidator : AbstractValidator<LikeTrackCommand>
{
    public LikeTrackCommandValidator()
    {
        RuleFor(c => c.TrackId).NotEmpty();
    }
}