#include "../include/eval.h"
#include <intrin.h>
#include <chrono>
using namespace std::chrono;

#define FLIP(sq) ((sq)^56)

int middleGamePieceValues[6] = { 100, 500, 320, 330, 900,  0 };
int endGamePieceValues[6] = { 120, 520, 300, 320, 900, 0 };


const int middleGamePawnTable[64] = {
      0,   0,   0,   0,   0,   0,  0,   0,
     98, 134,  61,  95,  68, 126, 34, -11,
     -6,   7,  26,  31,  65,  56, 25, -20,
    -14,  13,   6,  21,  23,  12, 17, -23,
    -27,  -2,  -5,  12,  17,   6, 10, -25,
    -26,  -4,  -4, -10,   3,   3, 33, -12,
    -35,  -1, -20, -23, -15,  24, 38, -22,
      0,   0,   0,   0,   0,   0,  0,   0,
};

const int middleGameRookTable[64] = {
     32,  42,  32,  51, 63,  9,  31,  43,
     27,  32,  58,  62, 80, 67,  26,  44,
     -5,  19,  26,  36, 17, 45,  61,  16,
    -24, -11,   7,  26, 24, 35,  -8, -20,
    -36, -26, -12,  -1,  9, -7,   6, -23,
    -45, -25, -16, -17,  3,  0,  -5, -33,
    -44, -16, -20,  -9, -1, 11,  -6, -71,
    -19, -13,   1,  17, 16,  7, -37, -26,
};

const int middleGameKnightTable[64] = {
    -105, -21, -58, -33, -17, -28, -19,  -23,
     -29, -53, -12,  -3,  -1,  18, -14,  -19,
     -23,  -9,  12,  10,  19,  17,  25,  -16,
     -13,   4,  16,  13,  28,  19,  21,   -8,
      -9,  17,  19,  53,  37,  69,  18,   22,
     -47,  60,  37,  65,  84, 129,  73,   44,
     -73, -41,  72,  36,  23,  62,   7,  -17,
    -167, -89, -34, -49,  61, -97, -15, -107,
};

const int middleGameBishopTable[64] = {
    -29,   4, -82, -37, -25, -42,   7,  -8,
    -26,  16, -18, -13,  30,  59,  18, -47,
    -16,  37,  43,  40,  35,  50,  37,  -2,
     -4,   5,  19,  50,  37,  37,   7,  -2,
     -6,  13,  13,  26,  34,  12,  10,   4,
      0,  15,  15,  15,  14,  27,  18,  10,
      4,  15,  16,   0,   7,  21,  33,   1,
    -33,  -3, -14, -21, -13, -12, -39, -21,
};

const int middleGameQueenTable[64] = {
    -28,   0,  29,  12,  59,  44,  43,  45,
    -24, -39,  -5,   1, -16,  57,  28,  54,
    -13, -17,   7,   8,  29,  56,  47,  57,
    -27, -27, -16, -16,  -1,  17,  -2,   1,
     -9, -26,  -9, -10,  -2,  -4,   3,  -3,
    -14,   2, -11,  -2,  -5,   2,  14,   5,
    -35,  -8,  11,   2,   8,  15,  -3,   1,
     -1, -18,  -9,  10, -15, -25, -31, -50,
};

const int middleGameKingTable[64] = {
    -65,  23,  16, -15, -56, -34,   2,  13,
     29,  -1, -20,  -7,  -8,  -4, -38, -29,
     -9,  24,   2, -16, -20,   6,  22, -22,
    -17, -20, -12, -27, -30, -25, -14, -36,
    -49,  -1, -27, -39, -46, -44, -33, -51,
    -14, -14, -22, -46, -44, -30, -15, -27,
      1,   7,  -8, -64, -43, -16,   9,   8,
    -15,  36,  12, -54,   8, -28,  24,  14,
};

const int endGamePawnTable[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
    178, 173, 158, 134, 147, 132, 165, 187,
     94, 100,  85,  67,  56,  53,  82,  84,
     32,  24,  13,   5,  -2,   4,  17,  17,
     13,   9,  -3,  -7,  -7,  -8,   3,  -1,
      4,   7,  -6,   1,   0,  -5,  -1,  -8,
     13,   8,   8,  10,  13,   0,   2,  -7,
      0,   0,   0,   0,   0,   0,   0,   0,
};

const int endGameRookTable[64] = {
    13, 10, 18, 15, 12,  12,   8,   5,
    11, 13, 13, 11, -3,   3,   8,   3,
     7,  7,  7,  5,  4,  -3,  -5,  -3,
     4,  3, 13,  1,  2,   1,  -1,   2,
     3,  5,  8,  4, -5,  -6,  -8, -11,
    -4,  0, -5, -1, -7, -12,  -8, -16,
    -6, -6,  0,  2, -9,  -9, -11,  -3,
    -9,  2,  3, -1, -5, -13,   4, -20,
};

const int endGameKnightTable[64]  = {
    -58, -38, -13, -28, -31, -27, -63, -99,
    -25,  -8, -25,  -2,  -9, -25, -24, -52,
    -24, -20,  10,   9,  -1,  -9, -19, -41,
    -17,   3,  22,  22,  22,  11,   8, -18,
    -18,  -6,  16,  25,  16,  17,   4, -18,
    -23,  -3,  -1,  15,  10,  -3, -20, -22,
    -42, -20, -10,  -5,  -2, -20, -23, -44,
    -29, -51, -23, -15, -22, -18, -50, -64,
};

const int endGameBishopTable[64] = {
    -14, -21, -11,  -8, -7,  -9, -17, -24,
     -8,  -4,   7, -12, -3, -13,  -4, -14,
      2,  -8,   0,  -1, -2,   6,   0,   4,
     -3,   9,  12,   9, 14,  10,   3,   2,
     -6,   3,  13,  19,  7,  10,  -3,  -9,
    -12,  -3,   8,  10, 13,   3,  -7, -15,
    -14, -18,  -7,  -1,  4,  -9, -15, -27,
    -23,  -9, -23,  -5, -9, -16,  -5, -17,
};

const int endGameQueenTable[64] = {
     -9,  22,  22,  27,  27,  19,  10,  20,
    -17,  20,  32,  41,  58,  25,  30,   0,
    -20,   6,   9,  49,  47,  35,  19,   9,
      3,  22,  24,  45,  57,  40,  57,  36,
    -18,  28,  19,  47,  31,  34,  39,  23,
    -16, -27,  15,   6,   9,  17,  10,   5,
    -22, -23, -30, -16, -16, -23, -36, -32,
    -33, -28, -22, -43,  -5, -32, -20, -41,
};

const int endGameKingTable[64] = {
    -74, -35, -18, -18, -11,  15,   4, -17,
    -12,  17,  14,  17,  17,  38,  23,  11,
     10,  17,  23,  15,  20,  45,  44,  13,
     -8,  22,  24,  27,  26,  33,  26,   3,
    -18,  -4,  21,  24,  27,  23,   9, -11,
    -19,  -3,  11,  21,  23,  16,   7,  -9,
    -27, -11,   4,  13,  14,   4,  -5, -17,
    -53, -34, -21, -11, -28, -14, -24, -43
};

const int* middleGameTables[6] =
{
    middleGamePawnTable,
    middleGameRookTable,
    middleGameKnightTable,
    middleGameBishopTable,
    middleGameQueenTable,
    middleGameKingTable
};

const int* endGameTables[6] =
{
    endGamePawnTable,
    endGameRookTable,
    endGameKnightTable,
    endGameBishopTable,
    endGameQueenTable,
    endGameKingTable
};

int middleGameMVVLVA[6][6];
int endGameMVVLVA[6][6];

int middleGamePreComputedValues[2][6][64];
int endGamePreComputedValues[2][6][64];

Move pvTable[64][64];
int pvLength[64];

vector<vector<Move>> killerMoves(64, vector<Move>(2)); //max depth of 64, storing 2 moves per depth
vector<vector<vector<int>>> historyMoves(2, vector<vector<int>>(6, vector<int>(64))); //2 colors 6 pieces 64 squares

int Evaluation::evaluate(const ChessBoard& board)
{
    return evaluatePieceSquareTables(board, 0) + evaluateMaterial(board, 1);
}

int Evaluation::evaluateMaterial(const ChessBoard &board, bool middleGame) 
{
    int score = 0;

    for(int pieceType = PieceType::PAWN; pieceType <= PieceType::KING; ++pieceType){
        auto whitePieceBoard = board.getPieceBoard(Piece(WHITE, static_cast<PieceType>(pieceType)));
        auto blackPieceBoard = board.getPieceBoard(Piece(BLACK, static_cast<PieceType>(pieceType)));

        int whitePieceCount = __builtin_popcountll(whitePieceBoard);
        int blackPieceCount = __builtin_popcountll(blackPieceBoard);

        score += whitePieceCount * (middleGame ? middleGamePieceValues[pieceType] : endGamePieceValues[pieceType]);
        score -= blackPieceCount * (middleGame ? middleGamePieceValues[pieceType] : endGamePieceValues[pieceType]);
    }

    return score;
}

void Evaluation::initializePieceSquareTables() {
    for (int pieceType = PieceType::PAWN; pieceType <= PieceType::KING; ++pieceType) {
        for (int square = 0; square < 64; ++square) {
            middleGamePreComputedValues[WHITE][pieceType][square] = middleGameTables[pieceType][square];
            middleGamePreComputedValues[BLACK][pieceType][square] = middleGameTables[pieceType][FLIP(square)];
            endGamePreComputedValues[WHITE][pieceType][square] = endGameTables[pieceType][square];
            endGamePreComputedValues[BLACK][pieceType][square] = endGameTables[pieceType][FLIP(square)];
        }
    }
}


int Evaluation::evaluatePieceSquareTables(const ChessBoard &board, bool isEndGame) {
    int score = 0;

    for (int pieceType = PieceType::PAWN; pieceType <= PieceType::KING; ++pieceType) {
        auto whitePieceBoard = BitBoard(board.getPieceBoard(Piece(WHITE, static_cast<PieceType>(pieceType))));
        auto blackPieceBoard = BitBoard(board.getPieceBoard(Piece(BLACK, static_cast<PieceType>(pieceType))));

        while (whitePieceBoard.getBoard()) {
            int square = whitePieceBoard.LS1B();
            whitePieceBoard.flipBit(square);
            if (isEndGame) {
                score += endGamePreComputedValues[WHITE][pieceType][63-square];
            } 
            else {
                score += middleGamePreComputedValues[WHITE][pieceType][63-square];
            }
        }

        while (blackPieceBoard.getBoard()) {
            int square = blackPieceBoard.LS1B();
            blackPieceBoard.flipBit(square);
            if (isEndGame) {
                score -= endGamePreComputedValues[BLACK][pieceType][63-square];
            } 

            else {
                score -= middleGamePreComputedValues[BLACK][pieceType][63-square];
            }
        }
    }

    return score;
}

int Evaluation::quiescenceSearch(ChessBoard &board, int whitesGuaranteedBestMove, int blacksGuaranteedBestMove, bool player) {
    //evaluate at leaf nodes
    int leafNodeEval = evaluate(board);

    //if leaf node eval exceed alpha beta bounds update them
    if (player) { 
        if (leafNodeEval >= blacksGuaranteedBestMove) {
            return blacksGuaranteedBestMove;
        }
        if (whitesGuaranteedBestMove < leafNodeEval) {
            whitesGuaranteedBestMove = leafNodeEval; 
        }
    } 
    else { 
        if (leafNodeEval <= whitesGuaranteedBestMove) {
            return whitesGuaranteedBestMove;
        }
        if (blacksGuaranteedBestMove > leafNodeEval) {
            blacksGuaranteedBestMove = leafNodeEval; 
        }
    }

    //search through captures
    vector<Move> captureMoves;
    board.generateCaptureMoves(player ? WHITE : BLACK, captureMoves);

    for (auto& move : captureMoves) {
        board.saveBoardState();
        if (!board.makeAMove(move)) {
            continue;
        }
        int score;
        if (player) {
            score = quiescenceSearch(board, whitesGuaranteedBestMove, blacksGuaranteedBestMove, !player);
        } 
        
        else {
            score = quiescenceSearch(board, whitesGuaranteedBestMove, blacksGuaranteedBestMove, !player);
        }
        board.restoreBoardState();

        //update alpha beta bounds
        if (player) { 
            if (score >= blacksGuaranteedBestMove) {
                return blacksGuaranteedBestMove; 
            }
            if (score > whitesGuaranteedBestMove) {
                whitesGuaranteedBestMove = score; 
            }
        } 
        
        else { 
            if (score <= whitesGuaranteedBestMove) {
                return whitesGuaranteedBestMove; 
            }
            if (score < blacksGuaranteedBestMove) {
                blacksGuaranteedBestMove = score;
            }
        }
    }

    return player ? whitesGuaranteedBestMove : blacksGuaranteedBestMove;
}

void Evaluation::initializeMVVLVA()
{
    for(int victim = PAWN; victim <= KING; victim++){
        for(int attacker = PAWN; attacker <= KING; attacker++){
            middleGameMVVLVA[victim][attacker] = middleGamePieceValues[victim] + 5000 - middleGamePieceValues[attacker];
            endGameMVVLVA[victim][attacker] = endGamePieceValues[victim] + 5000 - endGamePieceValues[attacker];
        }
    }
}

SearchResult Evaluation::minMax(ChessBoard &board, int depth, int whitesGuaranteedBestMove, int blacksGuaranteedBestMove, bool player, vector<Move>& pv) {
    //check the leaf nodes and avoid horizon effect
    if (depth == 0) {
        int eval = quiescenceSearch(board, whitesGuaranteedBestMove, blacksGuaranteedBestMove, player);
        return {eval, Move(), pv};
    }

    bool couldAMoveBeMade = false;
    SearchResult result;

    if (player) { // WHITE
        int maxEval = INT_MIN;
        Move bestMove;
        vector<Move> moveList;
        vector<Move> currentPV;
        board.generateMoves(WHITE, moveList);
        bool pvNodeFound = 0;

        sortMove(moveList, depth, pv);

        for (auto move : moveList) {  //iterate through moves
            board.saveBoardState();
            if (!board.makeAMove(move)) {
                continue;
            }
            couldAMoveBeMade = true;

            if(pvNodeFound){ //if a pv node is found, search it with a null window, to essentially "prove" that it is the best move
               result = minMax(board, depth - 1, whitesGuaranteedBestMove, whitesGuaranteedBestMove + 1, !player, currentPV);
               if(result.evaluation > whitesGuaranteedBestMove && result.evaluation < blacksGuaranteedBestMove){ //if it turns out that it isnt the best move, run a full search on it
                result = minMax(board, depth - 1, whitesGuaranteedBestMove, blacksGuaranteedBestMove, !player, currentPV);
               }
            }
            else{ //regular moves get a regualr search
                result = minMax(board, depth - 1, whitesGuaranteedBestMove, blacksGuaranteedBestMove, !player, currentPV);
            }
            
            board.restoreBoardState();

            if (result.evaluation > maxEval) { //you found the best mvoe in the position
                maxEval = result.evaluation;
                bestMove = move;
                pv.clear();
                pv.push_back(bestMove);
                pv.insert(pv.end(), result.pv.begin(), result.pv.end()); //update the pv
                pvNodeFound = 1; //you found a pv node
            }

            whitesGuaranteedBestMove = max(whitesGuaranteedBestMove, maxEval);  //update alpha bound
            if (blacksGuaranteedBestMove <= whitesGuaranteedBestMove) {  //Beta cutoff: prune the remaining branches as Black will not allow this move
                updateHistoryMoves(depth, move); //update history and killer moves on cutoff
                updateKillerMoves(depth, move);  
                break;
            }
        }
        if (couldAMoveBeMade) {
            // Debug print to show the PV at the current depth
            // cout << "Depth: " << depth << ", PV: ";
            // for (const auto& mv : pv) {
            //     board.printMove(mv.startingSquare, mv.endSquare);
            //     cout << " ";
            // }
            // cout << endl;
            return {maxEval, bestMove, pv};
        } 

        else {
            int kingSquare = BitBoard(board.getPieceBoard(Piece(WHITE, KING))).LS1B();
            bool inCheck = board.isSquareAttacked(kingSquare, BLACK);
            if (inCheck) {
                return {INT_MIN, Move(), pv}; //Checkmate
            } else {
                return {0, Move(), pv}; //Stalemate
            }
        }
    } 
    
    else { // BLACK
        int minEval = INT_MAX;
        Move bestMove;
        vector<Move> moveList;
        vector<Move> currentPV;
        board.generateMoves(BLACK, moveList);
        bool pvNodeFound = false;

        sortMove(moveList, depth, pv);

        for (auto move : moveList) {
            board.saveBoardState();
            if (!board.makeAMove(move)) {
                continue;
            }
            couldAMoveBeMade = true;

            if(pvNodeFound){
               result = minMax(board, depth - 1, blacksGuaranteedBestMove - 1, blacksGuaranteedBestMove, !player, currentPV);
               if(result.evaluation > whitesGuaranteedBestMove && result.evaluation < blacksGuaranteedBestMove){
                result = minMax(board, depth - 1, whitesGuaranteedBestMove, blacksGuaranteedBestMove, !player, currentPV);
               }
            }
            else{
                result = minMax(board, depth - 1, whitesGuaranteedBestMove, blacksGuaranteedBestMove, !player, currentPV);
            }           
            
            board.restoreBoardState();

            if (result.evaluation < minEval) {
                minEval = result.evaluation;
                bestMove = move;
                pv.clear();
                pv.push_back(bestMove);
                pv.insert(pv.end(), result.pv.begin(), result.pv.end());
                pvNodeFound = 1;
            }

            blacksGuaranteedBestMove = min(blacksGuaranteedBestMove, minEval); //update beta bound
            if (blacksGuaranteedBestMove <= whitesGuaranteedBestMove) { //Alpha cutoff: prune the remaining branches as White will not allow this move
                updateHistoryMoves(depth, move); //update history and killer moves on cutoff
                updateKillerMoves(depth, move);  
                break;
            }
        }
        if (couldAMoveBeMade) {
            // Debug print to show the PV at the current depth
            // cout << "Depth: " << depth << ", PV: ";
            // for (const auto& mv : pv) {
            //     board.printMove(mv.startingSquare, mv.endSquare);
            //     cout << " ";
            // }
            // cout << endl;
            return {minEval, bestMove, pv};
        } 
        else {
            int kingSquare = BitBoard(board.getPieceBoard(Piece(BLACK, KING))).LS1B();
            bool inCheck = board.isSquareAttacked(kingSquare, WHITE);
            if (inCheck) {
                return {INT_MAX, Move(), pv}; //Checkmate
            } else {
                return {0, Move(), pv}; //Stalemate
            }
        }
    }
}

SearchResult Evaluation::iterativeDeepeningSearch(ChessBoard &board, int depth, bool player) {
    SearchResult finalResult;
    vector<Move> pv;

    auto start = high_resolution_clock::now();

    for (int currentDepth = 1; currentDepth <= depth; ++currentDepth) {
        cout << "Starting search at depth: " << currentDepth << endl;
        finalResult = minMax(board, currentDepth, INT_MIN, INT_MAX, player, pv);
        cout << "Depth: " << currentDepth << " Best Move: ";
        board.printMove(finalResult.bestMove.startingSquare, finalResult.bestMove.endSquare);
        cout << " Evaluation: " << finalResult.evaluation << endl;
    }

    auto stop = high_resolution_clock::now(); // Stop timing
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Principal Variation: ";
    for (const Move& move : pv) {
        board.printMove(move.startingSquare, move.endSquare);
        cout << " "<<endl;
    }

    cout << "Time taken for search: " << duration.count() << " milliseconds" << endl;

    return finalResult;
}


int Evaluation::scoreMove(Move& move, int depth, const vector<Move>& pv) {

    if (pv.size() >= depth && move == pv[depth - 1]) {
        return 20000;
    }

    if (move == killerMoves[depth][0]) {
        return 10000;
    } 
    else if (move == killerMoves[depth][1]) {
        return 9000;
    }

    auto victim = move.capturedPiece.type;
    auto attacker = move.movingPieceType;
    auto historicScore = historyMoves[move.movingPieceColor][move.movingPieceType][move.endSquare];

    if(middleGame){
        return middleGameMVVLVA[victim][attacker] + historicScore;
    }
    else {
        return endGameMVVLVA[victim][attacker] + historicScore;
    }
}

inline void Evaluation::sortMove(vector<Move> &moveList, int depth, const vector<Move>& pv)
{
    vector<pair<Move, int>> sortedMoveList;
    sortedMoveList.reserve(moveList.size());

    for(auto move : moveList){
        sortedMoveList.emplace_back(make_pair(move, scoreMove(move,depth, pv)));
    }

    sort(sortedMoveList.begin(), sortedMoveList.end(), [](const pair<Move, int>& pair1, const pair<Move, int>& pair2){
        return pair1.second > pair2.second;
    }); //descending order

    moveList.clear(); 
    for (const auto& scoredMove : sortedMoveList) {
        moveList.push_back(scoredMove.first);
    }
}

void Evaluation::initializeKillerMoves() {
    for (auto& movesAtDepth : killerMoves) {
        movesAtDepth[0] = Move(-1, -1, EMPTY, WHITE, Piece(), EMPTY, false, false, false, false);
        movesAtDepth[1] = Move(-1, -1, EMPTY, WHITE, Piece(), EMPTY, false, false, false, false);
    }
}

void Evaluation::initializeHistoryMoves()
{
    for(auto& color : historyMoves){
        for(auto& pieces : color){
            fill(pieces.begin(), pieces.end(), 0);
        }
    }
}

void Evaluation::updateKillerMoves(int depth, const Move &move)
{
    if(move.capturedPiece.type == EMPTY){
        if(!(killerMoves[depth][0] == move) && !(killerMoves[depth][1] == move)){
            killerMoves[depth][1] = killerMoves[depth][0];
            killerMoves[depth][0] = move;
        }
    }
}

void Evaluation::updateHistoryMoves(int depth, const Move &move)
{
    if(move.capturedPiece.type == EMPTY){
        historyMoves[move.movingPieceColor][move.movingPieceType][move.endSquare] += depth * depth;
    }
}

// void Evaluation::testKillerAndHistoryMoves() {
//     ChessBoard board;

//     // Initialize the board with a specific FEN
//     board.initialize();
//     board.setBoardFromFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");

//     // Print the board
//     board.printChessBoard();

//     // Example search depth
//     int depth = 5;

//     // Initialize killer and history moves
//     initializeKillerMoves();
//     initializeHistoryMoves();

//     // White to move
//     SearchResult result = search(board, depth, INT_MIN, INT_MAX, true);

//     Move bestMove = result.bestMove;

//     board.printMove(bestMove.startingSquare, bestMove.endSquare);
//     std::cout << "   ";

//     std::cout << scoreMove(bestMove, depth) << std::endl;

//     // Print killer and history tables
//     std::cout << "Killer Moves:" << std::endl;
//     for (int d = 0; d < depth; ++d) {
//         std::cout << "Depth " << d << ": ";
//         for (const auto& move : killerMoves[d]) {
//             if (move.startingSquare != -1) {
//                 board.printMove(move.startingSquare, move.endSquare);
//                 std::cout << " ";
//             }
//         }
//         std::cout << std::endl;
//     }

//     std::cout << "History Moves:" << std::endl;
//     for (int color = 0; color < 2; ++color) {
//         for (int pieceType = 0; pieceType < 6; ++pieceType) {
//             std::cout << "Color " << color << ", Piece " << pieceType << ": ";
//             for (int square = 0; square < 64; ++square) {
//                 std::cout << historyMoves[color][pieceType][square] << " ";
//             }
//             std::cout << std::endl;
//         }
//     }
// }



void updatePV(vector<Move> &pv, const vector<Move> &childPV, const Move &move) {
    pv.clear();
    pv.push_back(move);
    pv.insert(pv.end(), childPV.begin(), childPV.end());
}

