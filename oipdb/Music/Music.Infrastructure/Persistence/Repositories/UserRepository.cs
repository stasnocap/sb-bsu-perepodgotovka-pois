using System.Reflection;
using Dapper;
using Microsoft.Extensions.Configuration;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.User;
using Music.Domain.User.ValueObjects;
using Music.Infrastructure.Persistence.Interceptors;
using BindingFlags = System.Reflection.BindingFlags;

namespace Music.Infrastructure.Persistence.Repositories;

public class UserRepository(IConfiguration configuration, PublishDomainEventsInterceptor publishDomainEventsInterceptor)
    : BaseRepository(configuration, publishDomainEventsInterceptor), IUserRepository
{

    public async Task<User?> SingleOrDefaultAsync(string email, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT * FROM ""Users"" WHERE ""Email"" = @Email";

        var user = (await Connection.QueryAsync<User>(sql, [typeof(UserDto)], 
                objs => ((UserDto)objs[0]).ToUser(), 
                new { Email = email }))
            .SingleOrDefault();

        return user;
    }

    public async Task AddAsync(User user, CancellationToken cancellationToken)
    {
        await BeginTransactionAsync(cancellationToken);

        const string sql =
            @"INSERT INTO ""Users""(""Id"", ""FirstName"", ""LastName"", ""Email"", ""Password"") VALUES (@Id, @FirstName, @LastName, @Email, @Password)";

        await Connection.ExecuteAsync(sql, new
        {
            Id = user.Id.Value, user.FirstName, user.LastName, user.Email, user.Password
        });

        await CommitAsync([user], cancellationToken);
    }

    private class UserDto
    {
        private static readonly ConstructorInfo Constructor =
            typeof(User).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];

        private static readonly ConstructorInfo IdConstructor =
            typeof(UserId).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];
        
        private static readonly ConstructorInfo FirstNameConstructor =
            typeof(FirstName).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];
        
        private static readonly ConstructorInfo LastNameConstructor =
            typeof(LastName).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];
        
        private static readonly ConstructorInfo EmailConstructor =
            typeof(Email).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];
        
        private static readonly ConstructorInfo PasswordConstructor =
            typeof(Password).GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic)[0];

        public Guid Id { get; init; }
        public string FirstName { get; init; }
        public string LastName { get; init; }
        public string Email { get; init; }
        public string Password { get; init; }

        public User ToUser()
        {
            var userId = IdConstructor.Invoke([Id]);
            var firstName = FirstNameConstructor.Invoke([FirstName]);
            var lastName = LastNameConstructor.Invoke([LastName]);
            var email = EmailConstructor.Invoke([Email]);
            var password = PasswordConstructor.Invoke([Password]);
            var user = Constructor.Invoke([userId, firstName, lastName, email, password]);
            return (User)user;
        }
    }
}