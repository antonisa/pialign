#ifndef PROB_HIER_H__
#define PROB_HIER_H__

#include "pialign/model-base.h"
#include <stdexcept>

namespace pialign {

class HierModel : public ProbModel {

public:

    HierModel() : ProbModel() { }
    
    Prob calcSentProb(const Span & mySpan) const { return 0; }

    Prob calcGenProb(WordId jId, const Span & mySpan) const {
        return log(phrases_.getProb(jId,0));
    }
    
    Prob calcBaseProb(const Span & mySpan, Prob baseMeas) const {
        PRINT_DEBUG(" HierModel::calcBaseProb @ "<<mySpan<<": "<<phraseFallback_<<"+"<<typeProbs_[TYPE_TERM]<<"+"<<baseMeas<<" == "<<phraseFallback_+typeProbs_[TYPE_TERM]+baseMeas<<std::endl, 2);
        return phraseFallback_+typeProbs_[TYPE_TERM]+baseMeas;
    }
    
    Prob calcTreeProb(const Span & mySpan, Prob myProb, const Span & yourSpan, Prob yourProb, int type) const {
        PRINT_DEBUG(" HierModel::calcTreeProb @ "<<mySpan<<"/"<<yourSpan<<" == ("<<phraseFallback_<<","<<typeProbs_[type]<<","<<myProb<<","<<yourProb<<") == "<< phraseFallback_+typeProbs_[type]+myProb+yourProb <<std::endl, 2);
        return phraseFallback_+typeProbs_[type]+myProb+yourProb;
    }

    Prob addSentence(const WordString & e, const WordString & f, SpanNode* node, StringWordSet & ePhrases, StringWordSet & fPhrases, PairWordSet & pairs, BaseMeasure* base);

    SpanNode* removePhrasePair(WordId jId, BaseMeasure* base);

    SpanNode* removeSentence(const SpanNode* head, BaseMeasure* base){
        if(head == 0) return 0;
        return removePhrasePair(head->phraseid,base);
    }

    bool isHierarchical() { return true; }
        
    void printPhraseTable(const WordSymbolSet & eVocab, const WordSymbolSet & fVocab, std::ostream & ptos) {
        throw std::runtime_error("HierModel::printPhraseTable not implemented");
    }

};

}

#endif
