<%@ Page Language="C#" %>

<html>
  <body>
      <form id="form1" runat="server">
    Нами принята следующая информация о Вас:<br><br>
    <ul>
      <%
        Response.Write ("<li>Имя: " + Request["Name"]);
        Response.Write ("<li>Адрес E-mail: " + Request["EMail"]);

        if (Request["Address"] != null) {
            StringBuilder sb =
                new StringBuilder ("<li>Почтовый адрес: ", 64);
            sb.Append (Request["Address"]);
            sb.Append (", ");
            sb.Append (Request["City"]);
            sb.Append (", ");
            sb.Append (Request["State"]);
            sb.Append (" ");
            sb.Append (Request["ZipCode"]);
            Response.Write (sb.ToString ());
        }

        if (Request["CreditCardNumber"] != null)
            Response.Write ("<li>Номер банковской карты: " +
                Request["CreditCardNumber"]);
      %>
    </ul>
   Спасибо! Ваши данные приняты. Ожидайте наши рекламные материалы!
      </form>
  </body>
</html>