using Music.Domain.Users;

namespace Music.Application.Common.Interfaces.Persistence;

public interface IUserRepository
{
    Task<User?> SingleOrDefaultAsync(string email, CancellationToken cancellationToken);
    Task AddAsync(User user, CancellationToken cancellationToken);
}