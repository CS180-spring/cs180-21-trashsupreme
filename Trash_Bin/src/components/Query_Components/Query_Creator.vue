<script lang="ts">
import { defineComponent } from 'vue';
import Query_Item from './Query_Item.vue';
import Query_Item_Selector from './Query_Item_Selector.vue';
import {Types} from '../../types'
import { sendQuery } from '@/requests';
import { oval_button } from '@/tailwindClasses';
    export default defineComponent ({
        data() {return {
            oval_button,
            keys: ["name", "extension"], //Hardcoded for now, could be dynamaic
            selected: new Map
        }},
        emits:['loaded'],
        components: {
            Query_Item,
            Query_Item_Selector
        },
        props: {
            name: String,
            value: String
        },
        created() {
            //Update keys with real values
        },
        methods: {
            addItem(key?:string, value?:string) {
                if (key != null && value != null) {
                    this.selected.set(key, value)
                }
            },
            async submit() {
                let data = sendQuery(this.keys, this.selected)
                data.then((value) => {
                    this.$emit('loaded', value)
                },
                (error) => {
                    console.log(error)
                }
                )
            }
        }
    })
</script>

<template>
    <Query_Item_Selector :options="keys" @submit="(key, value) => addItem(key, value)"/>
    <Query_Item v-for="item in selected" :name="item[0]" :value="item[1]" @delete="selected.delete(item[0])" />
    <div>
        <button @click="submit" :class=oval_button>Submit</button>
    </div>
</template>

<style>

</style>