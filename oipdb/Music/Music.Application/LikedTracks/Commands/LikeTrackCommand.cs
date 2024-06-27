using MediatR;
using Music.Domain.Tracks.ValueObjects;

namespace Music.Application.LikedTracks.Commands;

public record LikeTrackCommand(TrackId TrackId) : IRequest<ErrorOr.ErrorOr<TrackId>>;