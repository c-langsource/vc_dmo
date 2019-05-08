#include "domainoriented.h"

#include <Windows.h>

//通过枚举来框定数据选择范围

enum  _ModuleType {
	BASE=0,
	MODULE_NIC=1,
	MODULE_DISK = 2,
};
typedef  enum  _ModuleType ModuleType;



//模块就是一个 逻辑的容器
struct _ModuleBase;
typedef struct _ModuleBase ModuleBase;

struct _ModContext;
typedef struct _ModContext ModContext;


#define NAME_SIZE_LIMIT 30


struct _ModuleInerLogicOperation;
typedef struct _ModuleInerLogicOperation ModuleInerLogicOperation;


//方便扩展容器的内部业务逻辑的行为
struct _ModuleInerLogicOperation {
	int(*sendPack)(ModuleBase *this, int pack);
	void(*onSwitchOff)(ModuleBase *this);
	void(*onSwitchOn)(ModuleBase *this);
};


struct _ModuleBase {
	int mid;
	char name[30];

	//导航上下文信息
	ModContext *ctx;

	//容器的方法,生命周期的方法
	void(*init)(ModuleBase* this);
	void(*exit)(ModuleBase* this);
	void(*destrcut)(ModuleBase* this);
	void(*onSwitchOpt)(ModuleBase* this, ModuleInerLogicOperation * newOpt, ModuleInerLogicOperation *oldOpt);
	void(*onInitOpt)(ModuleBase* this, ModuleInerLogicOperation *opt);

	void(*destruct)(ModuleBase* this);
};


void ModuleBaseInit(ModuleBase* this);
void ModuleBaseExit(ModuleBase* this);
void ModuleBaseDestruct(ModuleBase*this);



ModuleBase * ModuleBaseConstruct(ModuleBase* this, int mid, const char *name) {
	this->mid = mid;
	strcpy_s(this->name, NAME_SIZE_LIMIT, name);
	this->init = ModuleBaseInit;
	this->exit = ModuleBaseExit;
	this->destrcut = ModuleBaseDestruct;


	return this;
}

int sendPack(ModuleBase *this, int pack) {


}




struct _ModContext {
	void(*regLogicOpt)(ModContext* this, int midx, ModuleInerLogicOperation *opt);
	void(*destruct)(ModContext* this);

};
void ModContextRegLogicOptImpl(ModContext* this, int midx, ModuleInerLogicOperation *opt);
void ModContextDestruct(ModContext *this);

ModContext* ModContextConstruct(ModContext *this) {
	this->regLogicOpt = ModContextRegLogicOptImpl;
	this->destruct = ModContextDestruct;
	return this;
}

void ModContextDestruct(ModContext *this) {


}



//ModuleCtl
ModuleCtl modctl;
void ModContextRegLogicOptImpl(ModContext* this, int midx, ModuleInerLogicOperation *opt) {
	ModuleCtlRegInnerLogicOpt(&modctl, midx, opt);

}


ModuleInerLogicOperation baseOpt;

void ModuleBaseInit(ModuleBase* this) {
	baseOpt.sendPack = sendPack;
	this->ctx->regLogicOpt(this->ctx,this->mid,&baseOpt);
}

void ModuleBaseExit(ModuleBase* this) {

}

void ModuleBaseDestruct(ModuleBase*this)
{

}


struct _NICMod;
typedef struct _NICMod NICMod;

struct _NICMod {
	ModuleBase base;


};


#define MODULE_Index_LIMIT 65535

struct _ModuleCtl;
typedef struct _ModuleCtl ModuleCtl;

struct _ModuleCtl {
	ModuleBase *mods[MODULE_Index_LIMIT];
	ModuleInerLogicOperation *opts[MODULE_Index_LIMIT];

};


#define MODULE_STATUS_NOT_EXISTED -1
#define MODULE_STATUS_OUT_OF_INDEX_RANGE -2
#define MODULE_STATUS_REISTER_NIL_OPT -3
#define MODULE_STATUS_REG_SAME_OPT -4


int ModuleCtlRegInnerLogicOpt(ModuleCtl* this,int midx , ModuleInerLogicOperation *opt) {
	if (this->mods[midx] == 0) return  MODULE_STATUS_NOT_EXISTED;
	if (opt == 0) return MODULE_STATUS_REISTER_NIL_OPT;
	ModuleInerLogicOperation *ori = 0;
	if (midx > MODULE_Index_LIMIT) return MODULE_STATUS_OUT_OF_INDEX_RANGE;
	
	ori = this->opts[midx];
	if (ori == opt) {
		return MODULE_STATUS_REG_SAME_OPT;
	}
	
	if (ori != 0) {
		if (ori->onSwitchOff != 0) {
			ori->onSwitchOff(ori);
		}
	}

	if (opt != 0) {
		if (opt->onSwitchOn!=0) {
			opt->onSwitchOn(opt);
		}
	
	}

	ModuleBase *m = this->mods[midx];
	m->onSwitchOpt(m, ori,opt);

}


void ModuleCtlPowerOnAll(ModuleCtl* this) {


}

void ModuleCtlPowerOn(ModuleCtl* this,int midx) {
	ModuleBase *m = 0;
	if (midx <= MODULE_Index_LIMIT) {
		m = this->mods[midx];
	}
	if (m != 0) {
		//doPrefitler(m->prefilter);
		m->init(m);
		//doPostfilter(m->postfilter);
	}
	 
}

void ModuleCtlPowerOff(ModuleCtl* this, int midx) {


}

static void doPrefitler(ModuleBase *target) {
	
}


static void doPostfilter(ModuleBase *target) {
	if (target == 0) return;
#if 0
	if (target->postfilter != 0) {
		doPostfilter(target->postfilter);
	}
	else {
		target->init(target);
		Sleep(10);
	}
#endif
}




int main(int argc, const char *argvs[]) {



	return 0;
}