using ErrorOr;
using MediatR;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Common.Interfaces.Services;
using Music.Domain.Artists.Errors;
using Music.Domain.LikedTracks;
using Music.Domain.Tracks.ValueObjects;
using Errors = Music.Domain.LikedTracks.Errors.Errors;

namespace Music.Application.LikedTracks.Commands;

public class LikeTrackCommandHandler(ILikedTrackRepository _likedTrackRepository, IUserContext _userContext):  IRequestHandler<LikeTrackCommand, ErrorOr<TrackId>>
{
    public async Task<ErrorOr<TrackId>> Handle(LikeTrackCommand request, CancellationToken cancellationToken)
    {
        var userId = _userContext.GetCurrentUserId();

        if (await _likedTrackRepository.AnyAsync(request.TrackId, userId, cancellationToken))
        {
            return Errors.LikedTrack.AlreadyExists;
        }

        var errorOrLikedTrack = LikedTrack.Create(request.TrackId, userId);
        if (errorOrLikedTrack.IsError)
        {
            return errorOrLikedTrack.Errors;
        }

        var likedTrack = errorOrLikedTrack.Value;

        await _likedTrackRepository.AddAsync(likedTrack, cancellationToken);

        return request.TrackId;
    }
}