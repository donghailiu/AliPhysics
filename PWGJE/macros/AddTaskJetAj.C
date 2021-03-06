

AliAnalysisTaskAj* AddTaskJetAj(const char* bRec1,const char* bRec2, UInt_t filterMask = 272 , Float_t ptTrackMin = 0.15, Int_t kTriggerMask=0, Int_t eventClassMin = 0, Int_t eventClassMax = 4){

   Printf("adding task jet response\n");

   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if(!mgr){
      ::Error("AddTaskJetAj", "No analysis manager to connect to.");
      return NULL;
   }
   if(!mgr->GetInputEventHandler()){
      ::Error("AddTaskJetAj", "This task requires an input event handler.");
      return NULL;
   }

     
  

  TString typeRec(bRec1);
  TString typeGen(bRec2);
      
  AliAnalysisTaskAj *task = new AliAnalysisTaskAj(Form("JetAj_%s_%s_%d",bRec1,bRec2,kTriggerMask));
   


   task->SetBranchNames(bRec1,bRec2);
   task->SetOfflineTrgMask(kTriggerMask);
   task->SetEvtClassMin(eventClassMin);
   task->SetEvtClassMax(eventClassMax);
   task->SetCentMin(0.);
   task->SetCentMax(100.);
   task->SetFilterMask(filterMask); 
 
   
   task->SetJetPtMin(0.);   
   //task->SetAngStructCloseTracks(1);

 

   mgr->AddTask(task);


   AliAnalysisDataContainer *coutputJetAj = mgr->CreateContainer(Form("pwgjeAj_%s_%s_%d",bRec1,bRec2,kTriggerMask), TList::Class(),AliAnalysisManager::kOutputContainer,Form("%s:PWGJE_jetAj_%s_%s_%d",AliAnalysisManager::GetCommonFileName(),bRec1,bRec2,kTriggerMask));





   mgr->ConnectInput (task, 0, mgr->GetCommonInputContainer());
   mgr->ConnectOutput(task, 0, mgr->GetCommonOutputContainer());
   mgr->ConnectOutput(task, 1, coutputJetAj);

   return task;
}
