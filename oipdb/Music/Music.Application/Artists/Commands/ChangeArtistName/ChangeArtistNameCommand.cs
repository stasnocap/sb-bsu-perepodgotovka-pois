using ErrorOr;
using MediatR;
using Music.Domain.Artists.ValueObjects;

namespace Music.Application.Artists.Commands.ChangeArtistName;

public record ChangeArtistNameCommand(ArtistId Id, string Name) : IRequest<ErrorOr<ArtistId>>;