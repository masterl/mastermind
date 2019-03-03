# MasterMind

C++ implementation of the game Mastermind for Foothill College CS 2A.

## Rules:

- Secret code length is 4

- Key "pegs":

<table>
  <tr>
    <th style="text-align:center">Code</th>
    <th style="text-align:center">Meaning</th>
  </tr>
  <tr>
    <td style="text-align:center">*</td>
    <td>when letters match on the same position</td>
  </tr>
  <tr>
    <td style="text-align:center">-</td>
    <td>when letters match on different positions</td>
  </tr>
  <tr>
    <td>(blank space)</td>
    <td>when letters don't match</td>
  </tr>
</table>

- Each guess or secret letter must match one to one

- \* takes precedence over -

### Examples:

<table>
  <tr>
    <th>Secret</th>
    <th>Guess</th>
    <th>Key</th>
  </tr>
  <tr>
    <td>torn</td>
    <td>mana</td>
    <td>-</td>
  </tr>
  <tr>
    <td>abby</td>
    <td>tube</td>
    <td>*</td>
  </tr>
  <tr>
    <td>case</td>
    <td>tara</td>
    <td>*</td>
  </tr>
  <tr>
    <td>case</td>
    <td>ebra</td>
    <td>--</td>
  </tr>
</table>

#### Authors:

- Xinyu Wen
- Leonardo de Oliveira Lourenço
