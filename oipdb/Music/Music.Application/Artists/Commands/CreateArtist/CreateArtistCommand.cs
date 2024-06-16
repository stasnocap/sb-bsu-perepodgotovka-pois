using ErrorOr;
using MediatR;

namespace Music.Application.Artists.Commands.CreateArtist;

public record CreateArtistCommand(string Name) : IRequest<ErrorOr<Guid>>;