<%@ Page Language="C#" %>

<html>
  <body>
    <%
      if (Session.IsNewSession || Session["Count"] == null) {
          Session["Count"] = 1;
          Response.Write ("Welcome! Because this is your first " +
              "visit to this site, a new session has been created " +
              "for you. Your session ID is " + Session.SessionID +
              ".");
      }
      else {
          Session["Count"] = (int) Session["Count"] + 1;
          Response.Write ("You have visited this site " +
              Session["Count"] + " times. Your session ID is still " +
              Session.SessionID + ".");
      }
    %>
  </body>
</html>