using ErrorOr;
using MediatR;
using Music.Domain.Artists.ValueObjects;

namespace Music.Application.Artists.Commands.CreateArtist;

public record CreateArtistCommand(string Name) : IRequest<ErrorOr<ArtistId>>;