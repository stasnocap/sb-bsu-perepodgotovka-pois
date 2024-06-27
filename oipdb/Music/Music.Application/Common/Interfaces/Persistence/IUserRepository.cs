using Music.Domain.Users;
using Music.Domain.Users.ValueObjects;

namespace Music.Application.Common.Interfaces.Persistence;

public interface IUserRepository
{
    Task<User?> SingleOrDefaultAsync(string email, CancellationToken cancellationToken);
    Task<User?> SingleOrDefaultAsync(UserId userId, CancellationToken cancellationToken);
    Task AddAsync(User user, CancellationToken cancellationToken);
}