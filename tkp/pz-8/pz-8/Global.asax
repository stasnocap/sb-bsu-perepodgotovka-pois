<%@ Import NameSpace="System.IO" %>

<script language="C#" runat="server">

  static Cache _cache = null;
  static string _path = null;

  void Application_Start ()
  {
      _cache = Context.Cache;
      _path = Server.MapPath ("Quotes.txt");

      ArrayList quotes = ReadQuotes ();

      if (quotes != null) {
          _cache.Insert ("Quotes", quotes, new CacheDependency (_path),
              Cache.NoAbsoluteExpiration, Cache.NoSlidingExpiration,
              CacheItemPriority.Default,
              new CacheItemRemovedCallback (RefreshQuotes));
      }
  }

  static void RefreshQuotes (String key, Object item,
      CacheItemRemovedReason reason)
  {
      ArrayList quotes = ReadQuotes ();

      if (quotes != null) {
          _cache.Insert ("Quotes", quotes, new CacheDependency (_path),
              Cache.NoAbsoluteExpiration, Cache.NoSlidingExpiration,
              CacheItemPriority.Default,
              new CacheItemRemovedCallback (RefreshQuotes));
      }
  }

  static ArrayList ReadQuotes ()
  {
      ArrayList quotes = new ArrayList ();
      StreamReader reader = null;

      try {
          reader = new StreamReader (_path);
          for (string line = reader.ReadLine (); line != null;
              line = reader.ReadLine ())
              quotes.Add (line);
      }
      catch (IOException) {
          return null;
      }
      finally {
          if (reader != null)
              reader.Close ();
      }
      return quotes;
  }
</script>