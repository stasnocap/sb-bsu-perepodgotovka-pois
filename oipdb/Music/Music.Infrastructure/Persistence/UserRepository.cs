﻿using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.Entities;

namespace Music.Infrastructure.Persistence;

public class UserRepository : IUserRepository
{
    private static readonly List<User> Users = new();
    
    public User? GetUserByEmail(string email)
    {
        return Users.SingleOrDefault(u => u.Email == email);
    }

    public void Add(User user)
    {
        Users.Add(user);
    }
}