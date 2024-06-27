using MediatR;
using ErrorOr;
using Music.Domain.Artists.ValueObjects;
using Music.Domain.Followers.ValueObjects;

namespace Music.Application.Followers.Commands.CreateFollower;

public record CreateFollowerCommand(ArtistId ArtistId) : IRequest<ErrorOr<FollowerId>>;