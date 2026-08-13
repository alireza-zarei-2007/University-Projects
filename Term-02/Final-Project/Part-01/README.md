<div align="center">

  <h1>🤠 UTGame - The Fastest Hand in the Middle East</h1>
  <p><b>Advanced Programming (AP) Assignment #5 | C++ Online Gaming & Turn-Based Duel System</b></p>

  <p>
    <img src="https://img.shields.io/badge/Language-C%2B%2B20-blue.svg" alt="C++20">
    <img src="https://img.shields.io/badge/Architecture-Object--Oriented-orange.svg" alt="OOP Architecture">
    <img src="https://img.shields.io/badge/Build-Makefile-green.svg" alt="Makefile">
  </p>

</div>

---

<h2>📌 Overview & Introduction</h2>
<p>
<b>UTGame</b> is an online multiplayer turn-based duel platform designed in C++20 using Object-Oriented Programming (OOP) principles[cite: 3]. The system simulates player authentication, casual dueling, dynamic matchmaking, turn-based combat mechanics ("shoot", "defend", "reload"), experience point (XP) updates, user profile tracking, and admin moderation for violation reporting[cite: 3].
</p>

---

<h2>🚀 Program Execution & Input Specifications</h2>

<p>The system is built using a multi-file structure with standard C++20 and is executed via CLI by passing paths to two CSV configuration files[cite: 3]:</p>

<pre>./UTGame &lt;/path/to/players.csv&gt; &lt;/path/to/admins.csv&gt;</pre>

<h3>1. Pre-Registered Players File (<code>players.csv</code>)</h3>
<p>Contains registered players with their username, password, and starting Experience Points (XP)[cite: 3].</p>

<pre>username, password, XP
pishikoochool, meooow, 2000
amir, italy, 900
iliya, ghasab, 1300</pre>

<h3>2. System Admins / Moderators File (<code>admins.csv</code>)</h3>
<p>Contains pre-configured system admins/moderators who monitor violations[cite: 3]. New admins cannot register at runtime[cite: 3].</p>

<pre>username, password
yasdan, ghomayshi
arshiya, cityfan</pre>

---

<h2>⚙️ System Architecture & Mechanics</h2>

<ul>
  <li><b>Command Syntax:</b> Commands begin with HTTP-like verbs (<code>POST</code>, <code>GET</code>, <code>PUT</code>, <code>DELETE</code>) followed by the command name, a <code>?</code> symbol, and key-value arguments separated by double quotes[cite: 3]. Argument order after <code>?</code> is non-deterministic[cite: 3].
    <br>Example: <code>POST invitation? username "pishilini" match_type "casual"</code>[cite: 3]
  </li>
  <li><b>User Types:</b>
    <ul>
      <li><b>Player:</b> Can register, log in, send/accept invitations, participate in duels, and view profiles[cite: 3]. Initial XP for new registrations is 500[cite: 3].</li>
      <li><b>Admin (Moderator):</b> Loaded via CSV at startup[cite: 3]. Admins cannot participate in matches or duels; they can only inspect submitted violation reports[cite: 3].</li>
    </ul>
  </li>
  <li><b>Global Auto-Increment IDs:</b> System entities like <b>Invitations</b> and <b>Violation Reports</b> use system-wide global IDs starting at <code>1</code>[cite: 3].</li>
  <li><b>Combat Mechanics:</b>
    <ul>
      <li>Each player starts a casual match with <b>1 bullet</b>[cite: 3].</li>
      <li>Actions per turn: <code>shoot</code>, <code>defend</code>, <code>reload</code>[cite: 3].</li>
      <li><code>reload</code> increases current bullet count by 1[cite: 3]. Shooting without bullets is invalid[cite: 3].</li>
      <li><b>Resolution Rules:</b>
        <ul>
          <li>If one shoots and the opponent reloads $\rightarrow$ The shooter wins immediately and the match ends[cite: 3].</li>
          <li>If both shoot $\rightarrow$ Bullets collide, nobody dies, both lose 1 bullet, and the match proceeds to the next turn[cite: 3].</li>
          <li>Other combinations (e.g., shooting against defend) $\rightarrow$ Nobody dies, game advances[cite: 3].</li>
        </ul>
      </li>
    </ul>
  </li>
  <li><b>XP Formula (Casual Match):</b>
    <br>Upon match completion, winner and loser XP update as follows[cite: 3]:
    <br>$$\Delta XP = \max\left(5, \; 50 - 0.1 \times (XP_{winner} - XP_{loser})\right)$$
    <br>$$XP_{new, winner} = XP_{winner} + \Delta XP$$
    <br>$$XP_{new, loser} = XP_{loser} - \Delta XP$$
  </li>
</ul>

---

<h2>⚠️ Priority Error Handling Hierarchy</h2>

<p>When executing commands, system errors must be evaluated in the exact following order[cite: 3]:</p>
<ol>
  <li><b>Method Verification:</b> Must start with <code>GET</code>, <code>POST</code>, <code>PUT</code>, or <code>DELETE</code>. Output: <code>Bad Request</code>[cite: 3].</li>
  <li><b>Command Existence:</b> The command must exist in the route table. Output: <code>Not Found</code>[cite: 3].</li>
  <li><b>Syntax/Format Validation:</b> Command arguments/format must be valid. Output: <code>Bad Request</code>[cite: 3].</li>
  <li><b>Access & Authorization:</b> User must be authenticated and authorized (e.g., logged in, or correct user role). Output: <code>Permission Denied</code>[cite: 3].</li>
  <li><b>Command-Specific Errors:</b> Handled as described in each command section[cite: 3].</li>
</ol>

---

<h2>🕹️ Commands & CLI Interaction Specifications</h2>

<h3>1. User Registration (<code>POST register</code>)</h3>
<p>Registers a new player with 500 initial XP and logs them in immediately[cite: 3].</p>

<b>Input Format:</b>
<pre>POST register ? username "&lt;username&gt;" password "&lt;password&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Bad Request</code> | <code>Permission Denied</code>[cite: 3]

<hr>

<h3>2. Login (<code>POST login</code>)</h3>
<p>Authenticates a registered player or admin[cite: 3].</p>

<b>Input Format:</b>
<pre>POST login ? username "&lt;username&gt;" password "&lt;password&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Not Found</code> | <code>Bad Request</code> | <code>Permission Denied</code>[cite: 3]

<hr>

<h3>3. Logout (<code>POST logout</code>)</h3>
<p>Logs out the currently active user session[cite: 3].</p>

<b>Input Format:</b>
<pre>POST logout ?</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code>[cite: 3]

<hr>

<h3>4. Casual Match Readiness Status (<code>POST casual_match_ready</code>)</h3>
<p>Sets the current player's readiness status for casual matchmaking[cite: 3].</p>

<b>Input Format:</b>
<pre>POST casual_match_ready ? status "&lt;true|false&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code>[cite: 3]

<hr>

<h3>5. Find Opponents (<code>GET casual_match_opponents</code>)</h3>
<p>Lists all ready players sorted by XP[cite: 3]. Default sort order is descending[cite: 3]. Tie-breaker: Username ascending[cite: 3].</p>

<b>Input Format:</b>
<pre>GET casual_match_opponents ? sort_order "&lt;asc|desc&gt;"</pre>

<b>Sample Output:</b>
<pre>1. pishi with 730 XP
2. iliya with 500 XP
3. pishilini with 300 XP</pre>

<hr>

<h3>6. Send Invitation (<code>POST invitation</code>)</h3>
<p>Sends a match invitation to another player[cite: 3]. Assigns a global <code>invitation_id</code>[cite: 3].</p>

<b>Input Format:</b>
<pre>POST invitation ? username "&lt;username&gt;" match_type "casual"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 3]

<hr>

<h3>7. Start Match (<code>POST start_match</code>)</h3>
<p>Accepts an invitation and initiates the duel[cite: 3]. Sets both players to "in game" status[cite: 3].</p>

<b>Input Format:</b>
<pre>POST start_match ? invitation_id "&lt;invitation_id&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 3]

<hr>

<h3>8. Reject Invitation (<code>POST reject_invitation</code>)</h3>
<p>Rejects and permanently deletes an invitation[cite: 3].</p>

<b>Input Format:</b>
<pre>POST reject_invitation ? invitation_id "&lt;invitation_id&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 3]

<hr>

<h3>9. Submit Turn Action (<code>POST action</code>)</h3>
<p>Registers a player's move for the current turn[cite: 3].</p>

<b>Input Format:</b>
<pre>POST action ? action "&lt;shoot|defend|reload&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 3]

<hr>

<h3>10. View Match Status (<code>GET match_status</code>)</h3>
<p>Displays turn number, current registered turn moves, remaining bullets, and turn history[cite: 3].</p>

<b>Input Format:</b>
<pre>GET match_status ?</pre>

<b>Sample Output:</b>
<pre>Turn 3
You: shoot
Your opponent: pending
History:
Opponent's moves:   Your moves:
defend              defend
shoot               defend
Your remaining bullets: 1</pre>

<hr>

<h3>11. Report Player Violation (<code>POST report</code>)</h3>
<p>Submits a violation report against a player to admins[cite: 3]. Generates a global <code>report_id</code>[cite: 3].</p>

<b>Input Format:</b>
<pre>POST report ? username "&lt;username&gt;" reason "&lt;message&gt;"</pre>

<b>Outputs:</b> <code>OK</code> | <code>Permission Denied</code> | <code>Bad Request</code> | <code>Not Found</code>[cite: 3]

<hr>

<h3>12. View Profile (<code>GET profile</code>)</h3>
<p>Displays XP, total wins, and total losses[cite: 3]. Defaults to self if username is omitted[cite: 3].</p>

<b>Input Format:</b>
<pre>GET profile ? username "&lt;username&gt;"</pre>

<b>Sample Output:</b>
<pre>username: "pishi"
XP: 2000
Total wins: 27
Total losses: 3</pre>

<hr>

<h3>13. View Received Invitations (<code>GET received_invitations</code>)</h3>
<p>Displays received invitations ordered from oldest to newest[cite: 3].</p>

<b>Input Format:</b>
<pre>GET received_invitations ?</pre>

<b>Sample Output:</b>
<pre>20: Invitation from "pishikoochool" for a "casual" match
41: Invitation from "pishibala" for a "casual" match</pre>

<hr>

<h3>14. View Reports - Admin Only (<code>GET reports</code>)</h3>
<p>Lists all filed violation reports[cite: 3]. Restricted to logged-in admins[cite: 3].</p>

<b>Input Format:</b>
<pre>GET reports ?</pre>

<b>Sample Output:</b>
<pre>1: "pishilini" reported "pishibala" for: "DDosing the server"
2: "amir" reported "pishikoochool" for: "Using hacks"</pre>

---

<h2>🛠️ Compilation & Setup Instructions</h2>

<p>The system must be modularized across multiple <code>.cpp</code> and <code>.hpp</code> files and built using a standard <code>Makefile</code> configured for C++20 standard[cite: 3]. The executable output must be named <code>UTGame</code> at the project root[cite: 3].</p>

<b>Build Commands:</b>
<pre>make
./UTGame ./players.csv ./admins.csv</pre>

---
