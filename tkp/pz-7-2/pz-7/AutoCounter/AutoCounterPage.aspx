<%@ Register TagPrefix="win" Namespace="Wintellect" Assembly="pz_7" %>
<%@ Page Language="C#" AutoEventWireup="true" CodeFile="AutoCounterPage.aspx.cs" Inherits="Wintellect.AutoCounterPage" %>

<html>
  <head>
    <title>Оценочная ведомость</title>
  </head>
  <body>
    <form runat="server">
      <h1>Оценочная ведомость</h1>
      <hr>
      
      <label>Фамилия:</label>
      <asp:TextBox ID="LastName" runat="server" />
      <br><br>
      
      <label>Предметы:</label>
      <table>
        <tr>
          <td>Предмет 1:</td>
          <td>
            <win:AutoCounter ID="Subject1Counter" Count="6"
              OnDecrement="OnDecrement" OnIncrement="OnIncrement"
              OnCountChanged="OnCountChanged" RunAt="server" />
          </td>
        </tr>
        <tr>
          <td>Предмет 2:</td>
          <td>
            <win:AutoCounter ID="Subject2Counter" Count="6"
              OnDecrement="OnDecrement" OnIncrement="OnIncrement"
              OnCountChanged="OnCountChanged" RunAt="server" />
          </td>
        </tr>
        <tr>
          <td>Предмет 3:</td>
          <td>
            <win:AutoCounter ID="Subject3Counter" Count="6"
              OnDecrement="OnDecrement" OnIncrement="OnIncrement"
              OnCountChanged="OnCountChanged" RunAt="server" />
          </td>
        </tr>
      </table>
      
      <br><br>
      <asp:Button Text="Подсчитать средний балл" OnClick="CalculateAverage" RunAt="server" />
      <hr>
      <asp:Label ID="Output" Runat="server" />
    </form>
  </body>
</html>
