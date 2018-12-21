// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESPIECE
#define CPPHESSCLASSESPIECE

#include "Board.h"

//! \brief Class Piece.
//!  Abstract base class for all pieces.
class Piece{
public:
  Piece( const Piece& )              = delete;
  Piece& operator = ( const Piece& ) = delete;
  Piece()                            = delete;
  virtual ~Piece(){}

  Piece( const PieceCoordinates& pcd,
         const PieceType& pt,
         const PieceColor& pcl ): pcoords_  ( pcd ),
                           ptype_           ( pt ),
                           pcolor_          ( pcl ),
                           isEverMoved_     ( false ),
                           isMovedOnlyOnce_ ( false ),
                           isMadeLongMove_  ( false ),
                           isUnderAttack_   ( false ){}



  //!<  Pure V.F. - each piece moves in a unique way and only inherits an interface.
  virtual bool move ( Board* board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j,
                      int32_t& i2,
                      int32_t& j2,
                      bool& isKingUnderAttack ) = 0;



  //!< General V.F. - some pieces use this behavior by default.
  virtual bool killForwardLine( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j,
                                int32_t& i2,
                                int32_t& j2,
                                bool& isKingUnderAttack );

  virtual bool killBackwardLine( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack );

  virtual bool killLeftLine( Board* board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j,
                             int32_t& i2,
                             int32_t& j2,
                             bool& isKingUnderAttack );

  virtual bool killRightLine( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j,
                              int32_t& i2,
                              int32_t& j2,
                              bool& isKingUnderAttack );



  virtual bool killForwardSquare( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j,
                                  int32_t& i2,
                                  int32_t& j2,
                                  bool& isKingUnderAttack );

  virtual bool killBackwardSquare( Board* board,
                                   const Player* player,
                                   Piece*& piece,
                                   const int32_t i,
                                   const int32_t j,
                                   int32_t& i2,
                                   int32_t& j2,
                                   bool& isKingUnderAttack );

  virtual bool killLeftSquare( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j,
                               int32_t& i2,
                               int32_t& j2,
                               bool& isKingUnderAttack );

  virtual bool killRightSquare( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j,
                                int32_t& i2,
                                int32_t& j2,
                                bool& isKingUnderAttack );



  virtual bool killDiagonalForwardLeftSquare( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j,
                                              int32_t& i2,
                                              int32_t& j2,
                                              bool& isKingUnderAttack );

  virtual bool killDiagonalBackwardRightSquare( Board* board,
                                                const Player* player,
                                                Piece*& piece,
                                                const int32_t i,
                                                const int32_t j,
                                                int32_t& i2,
                                                int32_t& j2,
                                                bool& isKingUnderAttack );

  virtual bool killDiagonalForwardRightSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j,
                                               int32_t& i2,
                                               int32_t& j2,
                                               bool& isKingUnderAttack );

  virtual bool killDiagonalBackwardLeftSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j,
                                               int32_t& i2,
                                               int32_t& j2,
                                               bool& isKingUnderAttack );



  virtual bool killDiagonalForwardLeftLine( Board* board,
                                            const Player* player,
                                            Piece*& piece,
                                            const int32_t i,
                                            const int32_t j,
                                            int32_t& i2,
                                            int32_t& j2,
                                            bool& isKingUnderAttack );

  virtual bool killDiagonalBackwardRightLine( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j,
                                              int32_t& i2,
                                              int32_t& j2,
                                              bool& isKingUnderAttack );

  virtual bool killDiagonalForwardRightLine( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j,
                                             int32_t& i2,
                                             int32_t& j2,
                                             bool& isKingUnderAttack );

  virtual bool killDiagonalBackwardLeftLine( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j,
                                             int32_t& i2,
                                             int32_t& j2,
                                             bool& isKingUnderAttack );



  virtual bool moveForwardSquare( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j,
                                  int32_t& i2,
                                  int32_t& j2,
                                  bool& isKingUnderAttack );

  virtual bool moveBackwardSquare( Board* board,
                                   const Player* player,
                                   Piece*& piece,
                                   const int32_t i,
                                   const int32_t j,
                                   int32_t& i2,
                                   int32_t& j2,
                                   bool& isKingUnderAttack );

  virtual bool moveLeftSquare( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j,
                               int32_t& i2,
                               int32_t& j2,
                               bool& isKingUnderAttack );

  virtual bool moveRightSquare( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j,
                                int32_t& i2,
                                int32_t& j2,
                                bool& isKingUnderAttack );



 virtual bool moveForwardLine2( Board* board,
                                const Player* player,
                                Piece*& piece,
                                const int32_t i,
                                const int32_t j,
                                int32_t& i2,
                                int32_t& j2,
                                bool& isKingUnderAttack,
                                const int32_t LENGTH );

  virtual bool moveBackwardLine2( Board* board,
                                  const Player* player,
                                  Piece*& piece,
                                  const int32_t i,
                                  const int32_t j,
                                  int32_t& i2,
                                  int32_t& j2,
                                  bool& isKingUnderAttack,
                                  const int32_t LENGTH );

  virtual bool moveLeftLine2( Board* board,
                              const Player* player,
                              Piece*& piece,
                              const int32_t i,
                              const int32_t j,
                              int32_t& i2,
                              int32_t& j2,
                              bool& isKingUnderAttack,
                              const int32_t LENGTH );

  virtual bool moveRightLine2( Board* board,
                               const Player* player,
                               Piece*& piece,
                               const int32_t i,
                               const int32_t j,
                               int32_t& i2,
                               int32_t& j2,
                               bool& isKingUnderAttack,
                               const int32_t LENGTH );



   virtual bool moveDiagonalForwardLeftLine( Board* board,
                                             const Player* player,
                                             Piece*& piece,
                                             const int32_t i,
                                             const int32_t j,
                                             int32_t& i2,
                                             int32_t& j2,
                                             bool& isKingUnderAttack,
                                             const int32_t LENGTH );

   virtual bool moveDiagonalBackwardLeftLine( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j,
                                              int32_t& i2,
                                              int32_t& j2,
                                              bool& isKingUnderAttack,
                                              const int32_t LENGTH );

   virtual bool moveDiagonalBackwardRightLine( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j,
                                               int32_t& i2,
                                               int32_t& j2,
                                               bool& isKingUnderAttack,
                                               const int32_t LENGTH );

   virtual bool moveDiagonalForwardRightLine( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j,
                                              int32_t& i2,
                                              int32_t& j2,
                                              bool& isKingUnderAttack,
                                              const int32_t LENGTH );



  virtual bool moveDiagonalForwardLeftSquare( Board* board,
                                              const Player* player,
                                              Piece*& piece,
                                              const int32_t i,
                                              const int32_t j,
                                              int32_t& i2,
                                              int32_t& j2,
                                              bool& isKingUnderAttack );

  virtual bool moveDiagonalBackwardRightSquare( Board* board,
                                                const Player* player,
                                                Piece*& piece,
                                                const int32_t i,
                                                const int32_t j,
                                                int32_t& i2,
                                                int32_t& j2,
                                                bool& isKingUnderAttack );

  virtual bool moveDiagonalForwardRightSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j,
                                               int32_t& i2,
                                               int32_t& j2,
                                               bool& isKingUnderAttack );

  virtual bool moveDiagonalBackwardLeftSquare( Board* board,
                                               const Player* player,
                                               Piece*& piece,
                                               const int32_t i,
                                               const int32_t j,
                                               int32_t& i2,
                                               int32_t& j2,
                                               bool& isKingUnderAttack );



  virtual bool movePiece( Board* board,
                          const Player* player,
                          Piece*& piece,
                          const int32_t i,
                          const int32_t j );

  virtual bool killPiece( Board* board,
                          const Player* player,
                          Piece*& piece,
                          const int32_t i,
                          const int32_t j,
                          bool& isKingUnderAttack );



  //!< Composite V.F. - some pieces have such moves as a part of behavior.
  virtual bool moveDiagonalSquare( Board* board,
                                   const Player* player,
                                   Piece*& piece,
                                   const int32_t i,
                                   const int32_t j,
                                   int32_t& i2,
                                   int32_t& j2,
                                   bool& isKingUnderAttack );

  virtual bool moveDiagonalLine( Board* board,
                                 const Player* player,
                                 Piece*& piece,
                                 const int32_t i,
                                 const int32_t j,
                                 int32_t& i2,
                                 int32_t& j2,
                                 bool& isKingUnderAttack );

  virtual bool movePerpendicularSquare( Board* board,
                                        const Player* player,
                                        Piece*& piece,
                                        const int32_t i,
                                        const int32_t j,
                                        int32_t& i2,
                                        int32_t& j2,
                                        bool& isKingUnderAttack );

  virtual bool movePerpendicularLine( Board* board,
                                      const Player* player,
                                      Piece*& piece,
                                      const int32_t i,
                                      const int32_t j,
                                      int32_t& i2,
                                      int32_t& j2,
                                      bool& isKingUnderAttack );

  virtual void setAsMadeLongMove( const bool isMadeLongMove ){
    isMadeLongMove_ = isMadeLongMove;
  }

  virtual bool isMadeLongMove() const{
    return isMadeLongMove_;
  }

  //!< Non-V.F. - all pieces use such functionality 'as is'.
  void setPieceCoordinates( const PieceCoordinates& p ){

    pcoords_ = p;
  }

  void setPieceType ( const PieceType& pt );
  void setPieceColor( const PieceColor& pc );

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

  const bool isMovedOnlyOnce() const{
    return isMovedOnlyOnce_;
  }

  const bool isUnderAttack() const{
    return isUnderAttack_;
  }

  void markAsUnderAttack(){
    isUnderAttack_ = true;
  }

  void markAsMoved(){

    if( !isEverMoved_ )
      isMovedOnlyOnce_ = true;
    else
      isMovedOnlyOnce_ = false;

    isEverMoved_ = true;
  }

protected:
  PieceCoordinates pcoords_;
  PieceType        ptype_;
  PieceColor       pcolor_;
  bool             isEverMoved_;
  bool             isMovedOnlyOnce_; // Control the fact of single piece movement
                                     //(important for long pawn moves)
  bool             isMadeLongMove_;
  bool             isUnderAttack_;

private:
  void replacePiece( Board* board,
                     const Player* player,
                     Piece*& winnerPieceSquare,
                     Piece*& looserPieceSquare,
                     const int32_t i,
                     const int32_t j );
};
#endif
