// C++HESS.
// Igor Lobanov. 2017
//
// This is a header file.

#ifndef C++LASSES
#define C++LASSES

class Piece;
//! \brief Show current pieces on board set.
void show( const std::vector<std::vector<Piece*> >& board );
void delay();
void clear();



//! \brief Class WinConsole.
class WinConsole{
public:
  void initialize();

  void showBoard( const std::vector<std::vector<Piece*> >& board );

  void delay();

  void clear();
};



//! \brief PieceCoordinates class.
//!
//! Keeps two coordinates:
//! - y (vertical coordinate)
//! - x (horizontal coordinate)
struct PieceCoordinates{
  int32_t y_;
  int32_t x_;

  //!< - 65 to convert char to int coordinates.
  PieceCoordinates( int32_t y = 0, int32_t x = 0 ):  y_( y ),
                                                             x_( x - 65 ) {}
};



//! \brief Exception class GameIsOver.
class GameIsOver{
};



//! \brief Class Game.
//!  Describes game process.
//!
//! Game validity state control:
//! - turns counter
//! - time control
class Game{
public:
  Game() : turns_(0), isValid_( true ) {}
  void nextTurn(){
    ++turns_;

    if (turns_ == TURNS_MAX)
      isValid_ = false;

    if (turns_ > TURNS_MAX)
      throw GameIsOver();
  }

  bool isRunning(){
    return isValid_;
  }

  const int32_t currentTurn() const{
    return turns_;
  }

    //!< Heads or tails game - who plays white.
    PieceColor headsOrTailsColor(){
      srand( time( nullptr ) );
      return rand() % 2 ? PieceColor::WHITE : PieceColor::BLACK;
    }

private:
  int32_t turns_;
  bool         isValid_;
};



//! \brief Class Board.
//!  Board keeps all pieces in its matrix-type container.
class Board{
public:
  Board(){
    board_.resize( HEIGHT );

    for( auto i = 0; i < HEIGHT; ++i )
    {
      board_[i].resize( WIDTH );
      for( auto j = 0; j < WIDTH; ++j )
          board_[i][j] = nullptr;
    }
  }

  void setPiece ( const Piece* p, int32_t x, int32_t y ){
    // To eliminate constness here is safe.
    board_ [y][x] = const_cast<Piece*>( p );
  }

  const int32_t getWidth ( ) const {
    return WIDTH;
  }

  const int32_t getHeight ( ) const {
    return HEIGHT;
  }

  const std::vector<std::vector<Piece*> >& readBoard() const{
    return board_;
  }

  std::vector<std::vector<Piece*> >& changeBoard() {
    return board_;
  }

private:
  std::vector<std::vector<Piece*> > board_;
};



class Player;
//! \brief Class Piece.
//!  Abstract base class for all pieces.
class Piece{
public:

  Piece( const Piece& )              = delete;
  Piece& operator = ( const Piece& ) = delete;
  Piece() = delete;
  virtual ~Piece(){}

  Piece( PieceCoordinates pcd,
                 PieceType pt,
                 PieceColor pcl): pcoords_     ( pcd ),
                                  ptype_       ( pt ),
                                  pcolor_      ( pcl ),
                                  isEverMoved_ ( false ) {}



  //!<  Pure V.F. - each piece moves in a unique way and only inherits this interface.
  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      int32_t i,
                      int32_t j ) = 0;



  //!< General V.F. - some pieces use such moves by default.
  virtual bool killForwardLine( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j );

  virtual bool killBackwardLine( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j );

  virtual bool killLeftLine( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j );

  virtual bool killRightLine( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j );



  virtual bool killForwardSquare( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  int32_t i,
                                  int32_t j );

  virtual bool killBackwardSquare( Board* board,
                                   const Player* player,
                                   Piece*& piece,
                                   const int32_t i,
                                   const int32_t j );

  virtual bool killLeftSquare( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j );

  virtual bool killRightSquare( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j );



  virtual bool killDiagonalForwardLeftSquare( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j );

  virtual bool killDiagonalBackwardRightSquare( Board* board,
                                                const Player* player,
                                                Piece*& piece,
                                                const int32_t i,
                                                const int32_t j );

  virtual bool killDiagonalForwardRightSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j );

  virtual bool killDiagonalBackwardLeftSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j );



  virtual bool killDiagonalForwardLeftLine( Board* board,
                                            const Player* player,
                                            Piece*& piece,
                                            const int32_t i,
                                            const int32_t j );

  virtual bool killDiagonalBackwardRightLine( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j );

  virtual bool killDiagonalForwardRightLine( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j );

  virtual bool killDiagonalBackwardLeftLine( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j );



  virtual bool moveForwardSquare( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j );

  virtual bool moveBackwardSquare( Board* board,
                                   const Player* player,
                                   Piece*& piece,
                                   const int32_t i,
                                   const int32_t j );

  virtual bool moveLeftSquare( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j );

  virtual bool moveRightSquare( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j );



 virtual bool moveForwardLine2( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j,
                                const int32_t LENGTH );

  virtual bool moveBackwardLine2( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j,
                                  const int32_t LENGTH );

  virtual bool moveLeftLine2( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j,
                              const int32_t LENGTH );

  virtual bool moveRightLine2( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j,
                               const int32_t LENGTH );



   virtual bool moveDiagonalForwardLeftLine( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j,
                                             const int32_t LENGTH );

   virtual bool moveDiagonalBackwardLeftLine( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j,
                                              const int32_t LENGTH );

   virtual bool moveDiagonalBackwardRightLine( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j,
                                               const int32_t LENGTH );

   virtual bool moveDiagonalForwardRightLine( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j,
                                              const int32_t LENGTH );



  virtual bool moveDiagonalForwardLeftSquare( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j );

  virtual bool moveDiagonalBackwardRightSquare( Board* board,
                                                const Player* player,
                                                Piece*& piece,
                                                const int32_t i,
                                                const int32_t j );

  virtual bool moveDiagonalForwardRightSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j );

  virtual bool moveDiagonalBackwardLeftSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j );



  virtual bool movePiece( Board* board,
                          Piece*& piece,
                          const int32_t i,
                          const int32_t j );

  virtual bool killPiece( Board* board,
                          Piece*& piece,
                          const int32_t i,
                          const int32_t j );



  //!< Composite V.F. - some pieces have such moves as a part of behavior.
  virtual bool moveDiagonalSquare( Board* board,
                                   const Player* player,
                                   Piece*& piece,
                                   const int32_t i,
                                   const int32_t j );

  virtual bool moveDiagonalLine( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j );

  virtual bool movePerpendicularSquare( Board* board,
                                        const Player* player,
                                        Piece*& piece,
                                        const int32_t i,
                                        const int32_t j );

  virtual bool movePerpendicularLine( Board* board,
                                      const Player* player,
                                      Piece*& piece,
                                      const int32_t i,
                                      const int32_t j );

  //!< Non-V.F. - all pieces use such functionality as is.
  void setPieceCoordinates( const PieceCoordinates& p );
  void setPieceType ( const PieceType& p );
  void setPieceColor( const PieceColor& p );

  const PieceType& getPieceType() const{
    return ptype_;
  }

  const PieceCoordinates& getPieceCoordinates() const{
    return pcoords_;
  }

  const PieceColor& getPieceColor() const{
    return pcolor_;
  }

  const bool isEverMoved() const{
    return isEverMoved_;
  }

  void markAsMoved(){
    isEverMoved_ = true;
  }

protected:
  bool hasCurrentThreat();
  bool isBattle( const PieceCoordinates& start,
                 const PieceCoordinates& finish );
  bool isSafeBattle( const PieceCoordinates& start,
                     const PieceCoordinates& finish );

  int32_t calcBattleBenefit( const PieceCoordinates& start,
                                 const PieceCoordinates& finish );
  void attack( const PieceCoordinates& s,
               const PieceCoordinates& f );
  bool isSafeReplace( const PieceCoordinates& start,
                      const PieceCoordinates& finish );
  void replace( const PieceCoordinates& s,
                const PieceCoordinates& f );

  PieceCoordinates pcoords_;
  PieceType        ptype_;
  PieceColor       pcolor_;
  bool             isEverMoved_;
};



//! \brief Class Queen.
//!  Queen piece.
class Queen: public Piece {
public:
  Queen( const Queen& )              = delete;
  Queen& operator = ( const Queen& ) = delete;
  Queen() = delete;

  Queen( PieceCoordinates pcd,
        PieceColor pcl): Piece( pcd, PieceType::QUEEN, pcl ) {}
  ~Queen() = default;

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j );
private:
};



//! \brief Class Pawn.
//!  Pawn piece.
class Pawn: public Piece {
public:
  Pawn( const Pawn& )              = delete;
  Pawn& operator = ( const Pawn& ) = delete;
  Pawn() = delete;

  Pawn( PieceCoordinates pcd,
        PieceColor pcl): Piece( pcd, PieceType::PAWN, pcl ) {}
  ~Pawn() = default;

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j );

  bool isLegalMove(  Board* board,
                    const PieceCoordinates& finish );
};



//! \brief Class Knight.
//!  Knight piece.
class Knight: public Piece {
public:
  Knight( const Knight& )              = delete;
  Knight& operator = ( const Knight& ) = delete;
  Knight() = delete;

  Knight( PieceCoordinates pcd,
        PieceColor pcl): Piece( pcd, PieceType::KNIGHT, pcl ) {}
  ~Knight() = default;

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j );



   bool moveForward2Right1( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool moveForward1Right2( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool moveForward2Left1( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j );

   bool moveForward1Left2( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j );

   bool moveBackward2Right1( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool moveBackward1Right2( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j );

   bool moveBackward2Left1( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool moveBackward1Left2( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );



   bool killForward2Right1( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool killForward1Right2( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool killForward2Left1( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j );

   bool killForward1Left2( Board* board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j );

   bool killBackward2Right1( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool killBackward1Right2( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool killBackward2Left1( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );

   bool killBackward1Left2( Board* board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j );
private:
};



//! \brief Class Bishop.
//!  Bishop piece.
class Bishop: public Piece {
public:
  Bishop( const Bishop& )              = delete;
  Bishop& operator = ( const Bishop& ) = delete;
  Bishop() = delete;

  Bishop( PieceCoordinates pcd,
        PieceColor pcl): Piece( pcd, PieceType::BISHOP, pcl ) {}
  ~Bishop() = default;

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j );
private:
};



//! \brief Class Rook.
//!  Rook piece.
class Rook: public Piece {
public:
  Rook( const Rook& )              = delete;
  Rook& operator = ( const Rook& ) = delete;

  Rook( PieceCoordinates pcd,
        PieceColor pcl): Piece( pcd, PieceType::ROOK, pcl ) {}
  ~Rook() = default;

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j );
private:
};



//! \brief Class King.
//!  King piece.
class King: public Piece {
public:
  King( const King& )              = delete;
  King& operator = ( const King& ) = delete;
  King() = delete;

  King( PieceCoordinates pcd,
        PieceColor pcl): Piece( pcd, PieceType::KING, pcl ) {}
  ~King() { throw GameIsOver(); }; //!< Kings never die.

  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j );
private:
};



//! \brief Class Player.
class Player{
public:
  Player( const std::string& name,
          Board* board,
          Game* game,
          PieceColor color );

  Player( const std::string& name,
          Board* board,
          Game* game,
          const Player& player );

  bool makeMove();
  bool makeRandomMove(); //!< EXPERIMENTAL

  void move( const PieceCoordinates& start,
             const PieceCoordinates& finish );

  const PieceColor& getColor() const;

  void showData() const;

  void arrangePieces( const int32_t scenario );

private:
  void queensBattle ();
  void pawnsBattle ();
  void classicBattle ();
  void kingsDance();
  void bishopVsRook ();
  void bishopVsKnight();
  void bishopVsPawn ();
  void kingsBattle();
  void randomBattle();

  void setMyTurnPriority ();

  std::string name_;
  Board*      board_;
  Game*       game_;
  PieceColor  color_;
  bool        isMyTurn_;
};
#endif
