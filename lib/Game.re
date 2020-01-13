type player =
  | PlayerOne
  | PlayerTwo;

type point =
  | Love
  | Fifteen
  | Thirty;

type pointsData = {
  playerOne: point,
  playerTwo: point
};
type fortyData = {
  player: player, /* The player who have forty points */
  otherPlayerPoint: point
};
let fd : fortyData = {player: PlayerOne, otherPlayerPoint: Love};
type score =
| Points(pointsData)
| Forty(fortyData)
| Deuce
| Advantage(player)
| Game(player);

let scoreWhenDeuce: player => score = winner => Advantage(winner);
let scoreWhenAdvantage: (player, player) => score =
  (advantagedPlayer, winner) =>
    advantagedPlayer == winner ? Game(winner) : Deuce;

/* This time we infer that the function type is (player) => player */
let other = player =>
  switch player {
  | PlayerOne => PlayerTwo
  | PlayerTwo => PlayerOne
};

let scoreWhenForty = (current, winner) => Game(winner);

/* We add a tool function to increment point */
let incrementPoint: point => option(point) =
  point =>
    switch point {
    | Love => Some(Fifteen)
    | Fifteen => Some(Thirty)
    | Thirty => None
    };

/* We add a tool function to increment point */
let incrementPoint: point => option(point) =
  point =>
    switch point {
    | Love => Some(Fifteen)
    | Fifteen => Some(Thirty)
    | Thirty => None
    };

let scoreWhenForty = (current, winner) =>
    current.player == winner ?
      Game(winner) :
      (
        switch (incrementPoint(current.otherPlayerPoint)) {
        | Some(p) => Forty({...current, otherPlayerPoint: p})
        | None => Deuce
        }
      );

let pointTo = (player, point, current) =>
switch player {
| PlayerOne => {...current, playerOne: point}
| PlayerTwo => {...current, playerTwo: point}
};

let pointFor = (player, current) =>
switch player {
| PlayerOne => current.playerOne
| PlayerTwo => current.playerTwo
};
    
let scoreWhenPoints = (current, winner) =>
  switch (current |> pointFor(winner) |> incrementPoint) {
  | Some(np) => Points(pointTo(winner, np, current))
  | None =>
    Forty({
      player: winner,
      otherPlayerPoint: current |> pointFor(other(winner))
    })
  };

let scoreWhenGame = winner => Game(winner);

let newGame = Points({playerOne: Love, playerTwo: Love});

let score = (current, winner) =>
  switch current {
  | Points(p) => scoreWhenPoints(p, winner)
  | Forty(f) => scoreWhenForty(f, winner)
  | Deuce => scoreWhenDeuce(winner)
  | Advantage(a) => scoreWhenAdvantage(a, winner)
  | Game(g) => scoreWhenGame(g)
  };

let string_of_player = (player) =>
  switch player {
  | PlayerOne => "PlayerOne"
  | PlayerTwo => "PlayerTwo"
};

let string_of_point = (point) =>
  switch point {
    | Love => "0"
    | Fifteen => "15"
    | Thirty => "30"
};


let string_of_score = (score) =>
  switch score {
    | Points(pointsData) => "PlayerOne : " ++ string_of_point(pointsData.playerOne) ++ " | PlayerTwo : " ++ string_of_point(pointsData.playerTwo)
    | Forty(fortyData) => switch fortyData.player {
      | PlayerOne => "Player One : 40 points | Player Two : " ++ string_of_point(fortyData.otherPlayerPoint) ++ " point(s)";
      | PlayerTwo =>"Player Two : 40 points | Player One : " ++ string_of_point(fortyData.otherPlayerPoint) ++ " point(s)";    
    }
    | Deuce => "40A"
    | Advantage(player) => "Advantage for " ++ string_of_player(player)
    | Game(_) => "Game"
};