using ErrorOr;
using MediatR;

namespace Music.Application.Artists.Commands.ChangeArtistName;

public record ChangeArtistNameCommand(Guid Id, string Name) : IRequest<ErrorOr<string>>;