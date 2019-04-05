// C++HESS.
// (C)Igor Lobanov. 2017
//
// This is a header file.

#ifndef CPPHESSCLASSESKNIGHT
#define CPPHESSCLASSESKNIGHT

#include "Pawn.h"

//! \brief Class Knight.
//!  Knight piece.
class Knight: public Piece {
public:
  Knight( const Knight& )              = delete;
  Knight& operator = ( const Knight& ) = delete;
  Knight()                             = delete;
  Knight( const PieceCoordinates& pcd,
          const PieceColor& pcl ): Piece( pcd, PieceType::KNIGHT, pcl ) {}
  ~Knight() = default;

  virtual bool move ( std::shared_ptr<Board> board,
                      const Player* player,
                      Piece*& piece,
                      const int32_t i,
                      const int32_t j,
                      int32_t& i2,
                      int32_t& j2,
                      bool& isKingUnderAttack ) override final;



   bool moveForward2Right1( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );

   bool moveForward1Right2( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );

   bool moveForward2Left1( std::shared_ptr<Board> board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j,
                           int32_t& i2,
                           int32_t& j2,
                           bool& isKingUnderAttack );

   bool moveForward1Left2( std::shared_ptr<Board> board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j,
                           int32_t& i2,
                           int32_t& j2,
                           bool& isKingUnderAttack );

   bool moveBackward2Right1( std::shared_ptr<Board> board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j,
                             int32_t& i2,
                             int32_t& j2,
                             bool& isKingUnderAttack );

   bool moveBackward1Right2( std::shared_ptr<Board> board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j,
                             int32_t& i2,
                             int32_t& j2,
                             bool& isKingUnderAttack );

   bool moveBackward2Left1( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );

   bool moveBackward1Left2( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );



   bool killForward2Right1( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );

   bool killForward1Right2( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );

   bool killForward2Left1( std::shared_ptr<Board> board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j,
                           int32_t& i2,
                           int32_t& j2,
                           bool& isKingUnderAttack );

   bool killForward1Left2( std::shared_ptr<Board> board,
                           const Player* player,
                           Piece*& piece,
                           const int32_t i,
                           const int32_t j,
                           int32_t& i2,
                           int32_t& j2,
                           bool& isKingUnderAttack );

   bool killBackward2Right1( std::shared_ptr<Board> board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j,
                             int32_t& i2,
                             int32_t& j2,
                             bool& isKingUnderAttack );

   bool killBackward1Right2( std::shared_ptr<Board> board,
                             const Player* player,
                             Piece*& piece,
                             const int32_t i,
                             const int32_t j,
                             int32_t& i2,
                             int32_t& j2,
                             bool& isKingUnderAttack );

   bool killBackward2Left1( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );

   bool killBackward1Left2( std::shared_ptr<Board> board,
                            const Player* player,
                            Piece*& piece,
                            const int32_t i,
                            const int32_t j,
                            int32_t& i2,
                            int32_t& j2,
                            bool& isKingUnderAttack );
private:
};
#endif
